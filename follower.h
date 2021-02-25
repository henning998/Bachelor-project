#ifndef FOLLOWER_H
#define FOLLOWER_H

#include "include.h"
#include "camera.h"
#include "Braitenberg.h"
#include "server.h"


class follower
{
private:
    camera picam;
    Braitenberg motor;
    server comm;
    enum state {GETTING_READY, FOLLOW, BACK_TO_NEST, BACK_TO_FOOD, BACK_TO_NEST_AGAIN, HOOKED_ON_A_FEELING};
    state diff_state = FOLLOW;
    std::vector<std::vector<double>> route_from_nest_to_food;
    std::vector<std::vector<double>> route_from_food_to_nest;

public:
    follower(/* args */);
    ~follower();
    void getting_Ready();
    void follow();
    void back_To_Nest();
    void back_To_Food();
    void back_To_Nest_Again(); 
    void run();
    void get_logging();
    void printlog();
    void reverse_Motor_values();
    
    void message_Handler();
    

    //void HOOKED_ON_A_FELLING(); //Hvis der er ekstra tid
};



#endif