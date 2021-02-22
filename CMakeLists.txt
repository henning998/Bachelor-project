cmake_minimum_required(VERSION 3.0.0)
project(bachelor VERSION 0.1.0)

include(CTest)
enable_testing()

find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})
<<<<<<< HEAD
add_executable(bachelor maintestserver.cpp controller.cpp server.cpp) #main.cpp controller.cpp Braitenberg.cpp camera.cpp client.cpp
=======
add_executable(bachelor client.cpp maintestclient.cpp controller.cpp Braitenberg.cpp camera.cpp) #main.cpp controller.cpp Braitenberg.cpp camera.cpp
>>>>>>> cf4c88c1313d65b0326324cf74974740f5149700
TARGET_LINK_LIBRARIES(bachelor matrix_creator_hal raspicam ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
