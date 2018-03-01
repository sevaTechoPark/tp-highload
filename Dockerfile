FROM ubuntu:16.04
MAINTAINER Vsevolod Papadyk
RUN apt-get update && apt-get install -y --no-install-recommends apt-utils
RUN apt-get -y install g++
RUN apt-get -y install libboost-all-dev

# ADD <src> <dest>
# Инструкция ADD скопирует <src> и добавит их в контейнер по пути <dest>
ADD /highload/ ./

RUN g++ src/*.cpp -lboost_thread -lboost_filesystem -std=c++14 -lboost_system -o httpd

EXPOSE 80

CMD ./httpd

