//
// Created by seva on 17.02.18.
//

#include <iostream>
#include "Connection.h"

Connection::Connection(boost::asio::io_service& io_service): socket_(io_service) {
}

void handler(const boost::system::error_code& error, std::size_t bytes_transferred) {
    std::cout << "handler" << std::endl;
}

void Connection::start() {

    std::string m_message = std::string("Hello World!");

    socket_.async_receive(boost::asio::buffer(buffer, 1024), 0, handler);

    boost::asio::async_write(
            socket_, boost::asio::buffer(m_message),
            boost::bind(&Connection::handle_write, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
}

void Connection::handle_write(const boost::system::error_code& a, size_t b) {
}