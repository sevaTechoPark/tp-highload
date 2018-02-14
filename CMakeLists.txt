cmake_minimum_required(VERSION 3.9)
project(highload)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.58.0 REQUIRED system)
include_directories(include)

add_executable(highload scr/main.cpp)
target_link_libraries(highload -lboost_thread ${Boost_LIBRARIES})