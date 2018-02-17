//
// Created by seva on 17.02.18.
//

#include <iostream>
#include "Connection.h"

Connection::Connection(boost::asio::io_service& io_service): socket(io_service) {
}

void Connection::start() {

    std::string m_message = std::string("Hello World!");

    socket.async_receive(
            boost::asio::buffer(buffer, 1024),
            boost::bind(&Connection::handleRead, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );

    boost::asio::async_write(
            socket, boost::asio::buffer(m_message),
            boost::bind(&Connection::handleWrite, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
}

void Connection::handleWrite(const boost::system::error_code &error_code, size_t size) {
    if (error_code) {
        std::cerr << "something wrong\n" << error_code;
    }
}

void Connection::handleRead(const boost::system::error_code &error_code, size_t size) {
    std::cout << buffer << std::endl;
    std::cout << size << std::endl;
    memset(buffer, 0, 1024);
}