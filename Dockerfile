FROM ubuntu:16.04
MAINTAINER Vsevolod Papadyk
RUN apt-get update && apt-get install -y --no-install-recommends apt-utils
RUN apt-get -y install g++
RUN apt-get -y install libboost-all-dev

ENV WORK /opt/highload
ADD /highload/ $WORK/
WORKDIR $WORK

RUN g++ src/*.cpp -lboost_thread -lboost_filesystem -std=c++14 -lboost_system -o httpd

EXPOSE 80

CMD ./httpd

