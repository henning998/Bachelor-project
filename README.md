# Bachelor-project
Robot collaborative navigation inspired by tandem runningbehaviour in ants

## How to run the code on both robots:
### Leader:
main:
```
 leader leaderobj;
 leaderobj.run();
``` 
### Follower:
main:
```
 follower followerobj;
 followerobj.run();
```

### Run the code:
First run the follower robot. Reason to run the follower robot first is due to it being the server
Secondly run the leader robot. 

## Requirements:
To run this code you need the following:
Screen, keyboard and mice to initialy get the robot started
Being able to connect up to the robot via VNC or similar program (Not a strict requirement)
Having a c++ compiler (used gcc 8.3.0)
Having opencv installed (version 2 or higher)

Optional if visual studio code is used:
Have cmake tools and cmake (version 3.0.0) installed

## Remember:
Braitenberg.h:
The value turn_tic is different for follower and leader, change the value accordingly

follower.cpp/leader.cpp
Depending on which of the two robots that is follower or leader, the PWM_factor variable need to be changed accordingly