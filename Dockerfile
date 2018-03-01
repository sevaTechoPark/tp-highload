FROM ubuntu:16.04

RUN apt-get -y update && apt-get install libboost-all-dev

ENV WORK /opt/highload
ADD Forum/ $WORK/
WORKDIR $WORK

RUN g++ src/*.cpp -lboost_thread -lboost_filesystem -std=c++14 -lboost_system -o httpd

EXPOSE 80

CMD ./httpd

