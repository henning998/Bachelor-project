cmake_minimum_required(VERSION 3.0.0)
project(bachelor VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(bachelor main.cpp controller.cpp Braitenberg.cpp)
TARGET_LINK_LIBRARIES(bachelor matrix_creator_hal)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
