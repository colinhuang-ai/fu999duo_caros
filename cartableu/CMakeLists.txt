cmake_minimum_required(VERSION 3.15)
project(car_sim CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CAR_SIM_SOURCES src/*.cpp)
add_executable(car_sim ${CAR_SIM_SOURCES})
