cmake_minimum_required(VERSION 3.9)
project(highload)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.58.0 REQUIRED system)
include_directories(include)

add_executable(httpd scr/main.cpp scr/Server.cpp scr/Server.h scr/Connection.cpp scr/Connection.h scr/Request.cpp scr/Request.h scr/Response.cpp scr/Response.h)
target_link_libraries(httpd -lboost_thread ${Boost_LIBRARIES})