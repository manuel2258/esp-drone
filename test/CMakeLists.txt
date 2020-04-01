cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

project(DroneTest)

set(INCLUDE_DIR ../main/src/)

add_executable(DroneTest ./tests/test_input_pkg.cpp ${INCLUDE_DIR}/pkg/input_pkg.cpp ${INCLUDE_DIR}/pkg/input_pkg.h)

target_include_directories(DroneTest PUBLIC ${INCLUDE_DIR}/pkg)

