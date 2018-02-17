//
// Created by seva on 17.02.18.
//

#include <iostream>
#include "Connection.h"

Connection::Connection(boost::asio::io_service& io_service): socket(io_service) {
}

void handler(const boost::system::error_code& error, std::size_t bytes_transferred) {
    std::cout << "handler" << std::endl;
}

void Connection::start() {

    std::string m_message = std::string("Hello World!");

    socket.async_receive(boost::asio::buffer(buffer, 1024), 0, handler);

    boost::asio::async_write(
            socket, boost::asio::buffer(m_message),
            boost::bind(&Connection::handleWrite, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
}

void Connection::handleWrite(const boost::system::error_code &a, size_t b) {
    if (a) {
        std::cerr << "something wrong\n" << a;
    }
}