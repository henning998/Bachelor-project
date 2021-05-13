#include "leader.h"

void leader::log_encoder()
{
    bool state_when_started = diff_state;
    std::cout << " In log encoder " << std::endl;
    std::vector<std::future<std::vector<int>>> async_vec; // Vector storing promises of vectors
    controller log_data;
    int head = 1, tail = 1;
    std::chrono::_V2::high_resolution_clock::time_point timer = std::chrono::high_resolution_clock::now(); // Create timer to the current instance
    while (diff_state == state_when_started)                                                               //Only run this thread when FOLLOW state is active
    {
        encoder_values.push_back(log_data.get_encode_values());
        if (FLAG_FOR_PUSHING_BACK_ENCODE_VALUE == true)
        {
            tail = head;
            head = encoder_values.size();
            std::chrono::_V2::high_resolution_clock::time_point end = timer;
            timer = std::chrono::high_resolution_clock::now();
            double time_elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(timer - end).count();
            timepoint.push_back(time_elapsed);

            async_vec.push_back(std::async(std::launch::deferred, &leader::tic_count, this, tail, head)); // Lazy evaluation to calculate and push back the result of tic_count
            FLAG_FOR_PUSHING_BACK_ENCODE_VALUE = false;
        }
    }
    for (int i = 0; i < async_vec.size(); i++)
    {
        std::vector<int> temp;
        temp = async_vec.at(i).get(); // Evaluation of tic_count
        left_encoder_tics.push_back(temp.at(0));
        right_encoder_tics.push_back(temp.at(1));
    }
}

std::vector<int> leader::tic_count(int tail, int head)
{
    int count_left = 0, count_right = 0;
    for (int i = tail; i < head; i++)
    {
        if (encoder_values.at(i).at(0) != encoder_values.at(i - 1).at(0) || encoder_values.at(i).at(1) != encoder_values.at(i - 1).at(1))
        {
            count_left++;
        }
        if (encoder_values.at(i).at(2) != encoder_values.at(i - 1).at(2) || encoder_values.at(i).at(3) != encoder_values.at(i - 1).at(3))
        {
            count_right++;
        }
    }
    std::vector<int> temp;
    temp.push_back(count_left);
    temp.push_back(count_right);
    return temp;
}

leader::leader()
{
    comm.connecting();

    gsl_vector_set_zero(X_Y_Theta);
}

leader::~leader()
{
}
void leader::find_Food()
{
    picam.change2red();
    std::thread log_thread(&leader::log_encoder, this);
    while (true)
    {
        picam.getpicture();
        cv::waitKey(27);
        float left = 0, right = 0;
        // Calculate how much the blob is to the left/right of the center
        blob_left_right(left, right);
        motor.love(left, right, picam.size);
        FLAG_FOR_PUSHING_BACK_ENCODE_VALUE = true;
        if (picam.size > 0.85) // When the robot is close enough to the blob
        {
            motor.stop();
            // get_logging();
            //printlog();
            diff_state = BACK_TO_NEST;
            usleep(100000);
            log_thread.join();
            // for (int i = 0; i < encoder_values.size(); i++)
            // {
            //     for (int j = 0; j < encoder_values.at(i).size(); j++)
            //     {
            //         //std::cout << encoder_values.at(i).at(j) << " ";
            //     }
            //     //std::cout << std::endl;
            // }
            //std::cout << "Size of encoder values: " << encoder_values.size() << std::endl;

            break;
        }
    }
}
void leader::back_To_Nest()
{
    picam.change2blue();
    position_direction();
    double theta = direction_vector();
    usleep(1000000);
    motor.turn(theta);
    usleep(1000000);
    for (int i = 0; i < left_encoder_tics.size(); i++)
    {
        std::vector<int> temp;
        temp.push_back(left_encoder_tics.at(i));
        temp.push_back(right_encoder_tics.at(i));
        encoder_tics.push_back(temp);
    }
    encode_tics_file.push_back(encoder_tics);
    timepoint_file.push_back(timepoint);
    gsl_vector_set_zero(X_Y_Theta);
    encoder_values.clear();
    left_encoder_tics.clear();
    right_encoder_tics.clear();
    std::thread log_thread(&leader::log_encoder, this);
    //go_straight(tics_from_food_to_nest);
    for (int i = 0; i < 10; i++)
    {
        if (i < 3)
        {
            go_straight(tics_from_food_to_nest / 10);
            FLAG_FOR_PUSHING_BACK_ENCODE_VALUE = true;
        }
        else
        {
            picam.getpicture();
            if (picam.new_pic)
            {
                while (picam.size < 0.85)
                {
                    i = 10; // break the for loop, when whille loop is complete
                    picam.getpicture();
                    float left = 0, right = 0;
                    // Calculate how much the blob is to the left/right of the center
                    blob_left_right(left, right);
                    motor.love(left, right, picam.size);
                    FLAG_FOR_PUSHING_BACK_ENCODE_VALUE = true;
                }
            }
            else
            {
                go_straight(tics_from_food_to_nest / 10);
                FLAG_FOR_PUSHING_BACK_ENCODE_VALUE = true;
            }
        }
    }
    diff_state = CALL_FOLLOWER;
    //usleep(100000);
    log_thread.join();
    //gsl_vector_set_zero(X_Y_Theta); // maybe
    position_direction();
    theta = direction_vector();
    usleep(1000000);
    motor.turn(theta);
}
void leader::call_Follower()
{
    usleep(500000);        // Sleep so server don't get spammed
    comm.writing("Ready"); // Ready to start tandem running
    comm.reader();
    if (comm.message == "I am here") // Wait for response from client
    {
        diff_state = GUIDE_FOLLOWER;
    }
}
void leader::guide_Follower()
{
    picam.change2red();
    gsl_vector_set_zero(X_Y_Theta);
    for (int i = 0; i < left_encoder_tics.size(); i++)
    {
        std::vector<int> temp;
        temp.push_back(left_encoder_tics.at(i));
        temp.push_back(right_encoder_tics.at(i));
        encoder_tics.push_back(temp);
    }
    encode_tics_file.push_back(encoder_tics);
    timepoint_file.push_back(timepoint);
    gsl_vector_set_zero(X_Y_Theta);
    encoder_values.clear();
    left_encoder_tics.clear();
    right_encoder_tics.clear();
    std::thread log_thread(&leader::log_encoder, this);
    // Drive on the logged motor values
    // for (int i = 0; i < route_from_nest_to_food.size(); i++)
    // {
    //     motor.set_motor_speed(route_from_nest_to_food.at(i).at(0), route_from_nest_to_food.at(i).at(1));
    //     usleep(route_from_nest_to_food.at(i).back() * 1000000); // From sec to mikrosec.
    // }
    for (int i = 0; i < 10; i++)
    {
        go_straight(tics_from_food_to_nest / 10);
        FLAG_FOR_PUSHING_BACK_ENCODE_VALUE = true;
        while (true)
        {
            comm.reader();
            if (comm.message == "Keep true")
            {
                break;
            }
        }
    }

    while (true)
    {
        usleep(500000); // Sleep so server don't get spammed
        comm.writing("Goal found");
        comm.reader();
        if (comm.message == "Okay move")
        {
            diff_state = MAKE_ROOM;
            log_thread.join();
            break;
        }
    }
}

void leader::make_room()
{
    picam.change2red();
    picam.getpicture();
    cv::waitKey(27);
    float left = 0, right = 0;
    // Calculate how much the blob is to the left/right of the center
    blob_left_right(left, right);
    std::thread log_thread(&leader::log_encoder, this);
    motor.fear(left, right, picam.size);
    usleep(time_to_fear);
    motor.stop();
    FLAG_FOR_PUSHING_BACK_ENCODE_VALUE = true;
    diff_state = BACK_TO_NEST_AGAIN;
    log_thread.join();
    position_direction();
    double theta = direction_vector();
    motor.turn(theta);
    comm.writing("I have moved");
    for (int i = 0; i < left_encoder_tics.size(); i++)
    {
        std::vector<int> temp;
        temp.push_back(left_encoder_tics.at(i));
        temp.push_back(right_encoder_tics.at(i));
        encoder_tics.push_back(temp);
    }
    encode_tics_file.push_back(encoder_tics);
    timepoint_file.push_back(timepoint);
    usleep(time_to_wait);
}

void leader::back_to_nest_again()
{
    picam.change2blue();
    //go_straight(tics_from_food_to_nest);

    for (int i = 0; i < 10; i++)
    {
        if (i < 3)
        {
            go_straight(tics_from_food_to_nest / 10);
        }
        else
        {
            picam.getpicture();
            if (picam.new_pic)
            {
                while (picam.size < 0.85)
                {
                    i = 10; // break the for loop, when whille loop is complete
                    picam.getpicture();
                    float left = 0, right = 0;
                    // Calculate how much the blob is to the left/right of the center
                    blob_left_right(left, right);
                    motor.love(left, right, picam.size);
                }
            }
            else
            {
                go_straight(tics_from_food_to_nest / 10);
            }
        }
    }

    //reverse_Motor_values();
    // Drive on the logged motor values
    // for (int i = 0; i < route_from_food_to_nest.size(); i++)
    // {
    //     motor.set_motor_speed(route_from_food_to_nest.at(i).at(0), route_from_food_to_nest.at(i).at(1));
    //     usleep(route_from_food_to_nest.at(i).back() * 1000000); // from sec to mikrosec.
    // }
    diff_state = TEST;
}

// void leader::get_logging()
// {
//     route_from_nest_to_food = motor.get_logging();
// }
// void leader::printlog()
// {
//     for (int i = 0; i < route_from_nest_to_food.size(); i++)
//     {
//         for (int j = 0; j < route_from_nest_to_food.at(i).size(); j++)
//         {
//             std::cout << route_from_nest_to_food.at(i).at(j) << " ";
//         }
//         std::cout << std::endl;
//     }
// }

void leader::run()
{
    while (run_leader)
    {
        switch (diff_state)
        {
        case FIND_FOOD:
            find_Food();
            break;
        case BACK_TO_NEST:
            back_To_Nest();
            break;
        case CALL_FOLLOWER:
            call_Follower();
            break;
        case GUIDE_FOLLOWER:
            guide_Follower();
            break;
        case MAKE_ROOM:
            make_room();
            break;
        case BACK_TO_NEST_AGAIN:
            back_to_nest_again();
            break;
        case TEST:
            file("/home/pi/HenningCasper/leader02.txt");
            //go_straight(20000); // 20500
            //find_Food();
            run_leader = false;
            break;
        default:
            break;
        }
    }
}

// void leader::reverse_Motor_values()
// {
//     route_from_food_to_nest = route_from_nest_to_food;
//     std::vector<double> temp = route_from_food_to_nest.back();
//     route_from_food_to_nest.pop_back();
//     for (int i = 0; i < route_from_food_to_nest.size(); i++)
//     {
//         std::swap(route_from_food_to_nest[i][0], route_from_food_to_nest[i][1]);
//     }

//     std::reverse(route_from_food_to_nest.begin(), route_from_food_to_nest.end());
//     route_from_food_to_nest.push_back(temp);

//     for (int i = 0; i < route_from_food_to_nest.size(); i++)
//     {
//         for (int j = 0; j < route_from_food_to_nest.at(i).size(); j++)
//         {
//             //   std::cout << route_from_food_to_nest.at(i).at(j) << " ";
//         }
//         // std::cout << std::endl;
//     }
// }

void leader::blob_left_right(float &left, float &right)
{
    if (picam.x < 150)
    {
        left = (150 - picam.x) / 150;
        right = 0;
    }
    if (picam.x > 170)
    {
        left = 0;
        right = (picam.x - 170) / 150;
    }
}

void leader::set_rotation_matrix(gsl_matrix &rotationmatrix, int i)
{
    double V_l = left_encoder_tics.at(i) / timepoint.at(i);
    double V_r = right_encoder_tics.at(i) / timepoint.at(i);
    double omega = (V_r - V_l) / center_of_wheel_base;
    double dt = timepoint.at(i);
    // std::cout << "i: " << i << std::endl;
    // std::cout << "V_l: " << V_l << std::endl;
    // std::cout << "V_r: " << V_r << std::endl;
    // std::cout << "Omega: " << omega << std::endl;
    // std::cout << "dt: " << dt << std::endl;
    // std::cout << "cos til delta t: " << cos(omega*dt) << std::endl;

    gsl_matrix_set(&rotationmatrix, 0, 0, cos(omega * dt));
    gsl_matrix_set(&rotationmatrix, 0, 1, -sin(omega * dt));
    gsl_matrix_set(&rotationmatrix, 0, 2, 0);
    gsl_matrix_set(&rotationmatrix, 1, 0, sin(omega * dt));
    gsl_matrix_set(&rotationmatrix, 1, 1, cos(omega * dt));
    gsl_matrix_set(&rotationmatrix, 1, 2, 0);
    gsl_matrix_set(&rotationmatrix, 2, 0, 0);
    gsl_matrix_set(&rotationmatrix, 2, 1, 0);
    gsl_matrix_set(&rotationmatrix, 2, 2, 1);
}

void leader::set_translation(gsl_vector &translation, int i)
{
    double V_l = left_encoder_tics.at(i) / timepoint.at(i);
    double V_r = right_encoder_tics.at(i) / timepoint.at(i);
    double R = (center_of_wheel_base / 2) * ((V_l + V_r) / (V_r - V_l));
    if (V_r - V_l == 0)
    {
        R = 0;
    }
    double ICC_x = gsl_vector_get(X_Y_Theta, 0) - R * sin(gsl_vector_get(X_Y_Theta, 2));
    double ICC_y = gsl_vector_get(X_Y_Theta, 1) + R * cos(gsl_vector_get(X_Y_Theta, 2));

    // std::cout << "i: " << i << std::endl;
    // std::cout << "V_l: " << V_l << std::endl;
    // std::cout << "V_r: " << V_r << std::endl;
    // std::cout << "R: " << R << std::endl;
    // std::cout << "ICC_x: " << ICC_x << std::endl;
    // std::cout << "ICC_y: " << ICC_y << std::endl;
    // std::cout << "x - ICC: " << gsl_vector_get(X_Y_Theta, 0) - ICC_x << std::endl;
    // std::cout << "y - ICC: " << gsl_vector_get(X_Y_Theta, 1) - ICC_y << std::endl;
    // std::cout << "theta: " << gsl_vector_get(X_Y_Theta, 2) << std::endl;

    gsl_vector_set(&translation, 0, gsl_vector_get(X_Y_Theta, 0) - ICC_x);
    gsl_vector_set(&translation, 1, gsl_vector_get(X_Y_Theta, 1) - ICC_y);
    gsl_vector_set(&translation, 2, gsl_vector_get(X_Y_Theta, 2));
}

void leader::set_icc(gsl_vector &ICC, int i)
{
    double V_l = left_encoder_tics.at(i) / timepoint.at(i);
    double V_r = right_encoder_tics.at(i) / timepoint.at(i);
    double omega = (V_r - V_l) / center_of_wheel_base;
    double dt = timepoint.at(i);
    double R = (center_of_wheel_base / 2) * ((V_l + V_r) / (V_r - V_l));
    if (V_r - V_l == 0)
    {
        R = 0;
    }
    double ICC_x = gsl_vector_get(X_Y_Theta, 0) - R * sin(gsl_vector_get(X_Y_Theta, 2));
    double ICC_y = gsl_vector_get(X_Y_Theta, 1) + R * cos(gsl_vector_get(X_Y_Theta, 2));
    //std::cout << "omega " << omega << " dt " << dt << " * " << omega * dt << std::endl;
    gsl_vector_set(&ICC, 0, ICC_x);
    gsl_vector_set(&ICC, 1, ICC_y);
    gsl_vector_set(&ICC, 2, omega * dt);
}

void leader::position_direction()
{
    // std::cout << "X_Y_Theta, x: " << gsl_vector_get(X_Y_Theta, 0) << std::endl;
    // std::cout << "X_Y_Theta, y: " << gsl_vector_get(X_Y_Theta, 1) << std::endl;
    // std::cout << "X_Y_Theta, theta: " << gsl_vector_get(X_Y_Theta, 2) << std::endl;
    gsl_matrix *rotation_matrix = gsl_matrix_alloc(3, 3);
    gsl_vector *translation = gsl_vector_alloc(3);
    gsl_vector *ICC = gsl_vector_alloc(3);
    for (int i = 0; i < left_encoder_tics.size(); i++)
    {
        set_rotation_matrix(*rotation_matrix, i);
        // for (int i = 0; i < 3; i++)
        // {
        //     for (int j = 0; j < 3; j++)
        //     {
        //         std::cout << " " << gsl_matrix_get(rotation_matrix, i, j);
        //     }

        //     std::cout << std::endl;
        // }

        set_translation(*translation, i);
        // for (int j = 0; j < 3; j++)
        // {
        //     std::cout << " " << gsl_vector_get(translation, j);
        // }
        // std::cout << std::endl;
        set_icc(*ICC, i);

        gsl_blas_dgemv(CblasNoTrans, 1.0, rotation_matrix, translation, 0, X_Y_Theta);
        gsl_blas_daxpy(1.0, ICC, X_Y_Theta);
        // std::cout << "X_Y_Theta, x: " << gsl_vector_get(X_Y_Theta, 0) << std::endl;
        // std::cout << "X_Y_Theta, y: " << gsl_vector_get(X_Y_Theta, 1) << std::endl;
        // std::cout << "X_Y_Theta, theta: " << gsl_vector_get(X_Y_Theta, 2) << std::endl;
    }
    gsl_matrix_free(rotation_matrix);
    gsl_vector_free(translation);
    gsl_vector_free(ICC);
}

double leader::direction_vector()
{
    theta_param = 0.0;
    tics_from_food_to_nest = sqrt(pow(gsl_vector_get(X_Y_Theta, 0), 2) + pow(gsl_vector_get(X_Y_Theta, 1), 2));
    route_length.push_back(tics_from_food_to_nest);
    //std::cout << "tics from food to nest: " << tics_from_food_to_nest << std::endl;

    double theta_turn, theta_nest_food;

    theta_nest_food = asin(gsl_vector_get(X_Y_Theta, 1) / tics_from_food_to_nest);
    // std::cout << "theta nest food: " << theta_nest_food << std::endl;

    theta_turn = M_PI + (gsl_vector_get(X_Y_Theta, 2) - theta_nest_food);
    // std::cout << "theta_turn: " << theta_turn << std::endl;

    if (theta_turn > M_PI)
    {
        theta_turn = theta_turn - 2 * M_PI;
    }

    theta_param = theta_turn;
    theta_file.push_back(theta_param);

    return theta_turn;
}

void leader::go_straight(int tics_to_go)
{
    float min_speed = motor.parameters().at(1);
    double PWM_change_factor = 0.04275; //test 08: 0.1, 0.05, 0.01, 0.005, 0.5
    int tics_r = 0, tics_l = 0;
    controller log_encode;
    std::vector<int> last_run = log_encode.get_encode_values();
    std::vector<double> time;
    while (tics_r <= tics_to_go || tics_l <= tics_to_go) //4523
    {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        std::vector<int> temp = log_encode.get_encode_values();
        // for (int i = 0; i < temp.size(); i++)
        // {
        //     std::cout<<temp.at(i) << " " ;
        // }
        // std::cout << std::endl;

        if (temp.at(0) != last_run.at(0) || temp.at(1) != last_run.at(1))
        {
            tics_l++;
        }
        if (temp.at(2) != last_run.at(2) || temp.at(3) != last_run.at(3))
        {
            tics_r++;
        }
        last_run = temp;
        if (tics_r <= tics_to_go)
        {
            int diff_r = 0;
            if (tics_r < tics_l)
            {
                diff_r = (tics_l - tics_r) * PWM_change_factor;
                //   std::cout << "diff_r: " << diff_r << std::endl;
            }

            log_encode.setRightMotorSpeedDirection(min_speed + diff_r, forward);
        }
        else
        {
            log_encode.setRightMotorSpeedDirection(0, forward);
            log_encode.setLeftMotorSpeedDirection(0, forward);
            tics_l = tics_to_go + 1;
        }

        if (tics_l <= tics_to_go)
        {
            int diff_l = 0;
            if (tics_l < tics_r)
            {
                diff_l = (tics_r - tics_l) * PWM_change_factor;
                //   std::cout << "diff_l: " << diff_l << std::endl;
            }

            log_encode.setLeftMotorSpeedDirection(min_speed + diff_l, forward);
        }
        else
        {
            log_encode.setLeftMotorSpeedDirection(0, forward);
            log_encode.setRightMotorSpeedDirection(0, forward);
            tics_r = tics_to_go + 1;
        }
        //std::cout << "tics_l: " << tics_l << " & tics_r: " << tics_r << std::endl;
        end = std::chrono::system_clock::now();
        double time_elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(start - end).count();
        time.push_back(time_elapsed);
        //std::cout << "time_elapsed " << time_elapsed << std::endl;
        //usleep(5);
    }
    // for (int i = 0; i < time.size(); i++)
    // {
    //     std::cout << time.at(i) << std::endl;
    // }
}

void leader::file(std::string file_name)
{
    std::ofstream my_file(file_name);
    std::vector<float> param = motor.parameters();
    my_file << "Braitenberg parameters \n";
    my_file << "MaxSpeed: " << param.at(0) << "\n";
    my_file << "MinSpeed: " << param.at(1) << "\n";
    my_file << "centerweight: " << param.at(2) << "\n";
    my_file << "distweight: " << param.at(3) << "\n";
    my_file << "turn_tic: " << param.at(4) << "\n";
    my_file << "Max tics to move back: " << param.at(5) << "\n";
    my_file << "Actual tics moved back: " << param.at(5) * abs(cos(theta_param)) << "\n\n";

    my_file << "Leader parameters \n";
    my_file << "Fear (how much time we fear): " << time_to_fear << "\n";
    my_file << "Wait (How much time we wait before going back): " << time_to_wait << "\n";

    for (int i = 0; i < theta_file.size(); i++)
    {
        my_file << "Theta (how much the robot turn): " << i << ": "<< theta_file.at(i) << "\n";
    }

    for (int i = 0; i < route_length.size(); i++)
    {
        my_file << "Tics from food to nest " << i << ": " << route_length.at(i) << "\n";
    }

    my_file << "\n";

    my_file << "Encoder shift (tics): \n";
    for (int j = 0; j < encode_tics_file.size(); j++)
    {
        my_file << j << ": ";

        for (int i = 0; i < encode_tics_file[j].size(); i++)
        {
            my_file << "Left: " << encode_tics_file[j][i][0] << " Right: " << encode_tics_file[j][i][1] << " Time: " << timepoint_file[j][i] << "\n";
        }
        my_file << "\n\n";
    }
}