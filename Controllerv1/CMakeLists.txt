cmake_minimum_required(VERSION 3.0.0)
project(controller VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(controller main.cpp)
TARGET_LINK_LIBRARIES(controller matrix_creator_hal)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
