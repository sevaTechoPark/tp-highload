cmake_minimum_required(VERSION 3.9)
project(highload)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.58.0 REQUIRED system)
include_directories(include)

add_executable(httpd src/main.cpp src/Server.cpp src/Server.h src/Connection.cpp src/Connection.h src/Request.cpp src/Request.h src/Response.cpp src/Response.h)
target_link_libraries(httpd -lboost_thread -lboost_filesystem ${Boost_LIBRARIES})