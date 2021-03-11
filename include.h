#ifndef INCLUDE_H
#define INCLUDE_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <thread>
#include <string>
#include <stdio.h>      //Standard input and output library
#include <stdlib.h>     //This includes functions regarding memory allocation
#include <string.h>     //Contains string functions
#include <errno.h>      //It defines macros for reporting and retrieving error conditions through error codes
#include <time.h>       //Contains various functions for manipulating date and time
#include <unistd.h>     //Contains various constants
#include <sys/types.h>  //Contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h>  //Defines in_addr structure
#include <sys/socket.h> //For socket creation
#include <netinet/in.h> //Contains constants and structures needed for internet domain addresses
#include <netdb.h>
#include <cctype>
#include <chrono>
#include <thread>
#include <future>
#include <list>

#include <raspicam/raspicam.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/core/ocl.hpp>

#endif