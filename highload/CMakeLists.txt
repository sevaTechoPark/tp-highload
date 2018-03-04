cmake_minimum_required(VERSION 3.9)
project(highload)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.58.0 REQUIRED system)
include_directories(include)

add_executable(httpd src/main.cpp src/Server.cpp headers/Server.h src/Connection.cpp headers/Connection.h src/Request.cpp headers/Request.h src/Response.cpp headers/Response.h)
target_link_libraries(httpd -lboost_thread -lboost_filesystem ${Boost_LIBRARIES})