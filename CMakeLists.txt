cmake_minimum_required(VERSION 3.0.0)
project(bachelor VERSION 0.1.0)

include(CTest)
enable_testing()

find_package( OpenCV REQUIRED)
find_package( Threads )
include_directories( ${OpenCV_INCLUDE_DIRS})
add_executable(bachelor main.cpp controller.cpp Braitenberg.cpp camera.cpp leader.cpp client.cpp follower.cpp server.cpp) #main.cpp controller.cpp Braitenberg.cpp camera.cpp
TARGET_LINK_LIBRARIES(bachelor matrix_creator_hal raspicam ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
