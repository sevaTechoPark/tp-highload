cmake_minimum_required(VERSION 3.9)
project(highload)

set(CMAKE_CXX_STANDARD 11)

set(BOOST_ROOT "/path_to_boost_1_58_0")

find_package(Boost 1.58.0)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()

add_executable(highload main.cpp)