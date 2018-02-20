//
// Created by seva on 17.02.18.
//

#include <iostream>
#include "Connection.h"

Connection::Connection(boost::asio::io_service &io_service, string rootDir): socket(io_service), request(rootDir) {
}

void Connection::start() {

    socket.async_receive(
            boost::asio::buffer(buffer, bufferSize),
            boost::bind(&Connection::handleRead, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
}

void Connection::handleRead(const boost::system::error_code &error_code, size_t size) {
    request.parseRequest(std::string(buffer), size,
                         std::bind(&Connection::sendMessage, shared_from_this(), std::placeholders::_1),
                         std::bind(&Connection::sendFile, shared_from_this(), std::placeholders::_1, std::placeholders::_2));

    memset(buffer, 0, 1024);
}

void Connection::sendMessage(const std::string &message) {
     socket.write_some(boost::asio::buffer(message));
}

void Connection::sendFile(int fd, size_t size){
    startOfft = 0;
    sendfile(socket.native(), fd, &startOfft, size - startOfft);
    close(socket.native());
}

