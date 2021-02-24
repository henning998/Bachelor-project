#ifndef LEADER_H
#define LEADER_H

#include "include.h"
#include "camera.h"
#include "Braitenberg.h"
#include "client.h"


class leader
{
private:
    camera picam;
    Braitenberg motor;
    client comm;
    enum state {FIND_FOOD,BACK_TO_NEST,CALL_FOLLOWER,GUIDE_FOLLOWER,MAKE_ROOM};
    state diff_state = FIND_FOOD;
    std::vector<std::vector<double>> route_from_nest_to_food;
    std::vector<std::vector<double>> route_from_food_to_nest;
    
public:
    leader(/* args */);
    ~leader();
    void find_Food();
    void back_To_Nest();
    void call_Follower();
    void guide_Follower();
    // so follower can see the food
    void make_room(); 
    void run();
    void get_logging();
    void printlog();
    void reverse_Motor_values();
    // NEED THE LAST BACK TO NEST
 
    //void HOOKED_ON_A_FELLING(); //Hvis der er ekstra tid
};



#endif