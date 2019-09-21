cmake_minimum_required(VERSION 3.13)
project(irz)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-lm -lpigpio -pthread")

add_executable(irz main.cpp decoder.cpp decoder.h)
