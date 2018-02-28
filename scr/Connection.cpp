//
// Created by seva on 17.02.18.
//

#include <iostream>
#include <boost/thread/thread.hpp>
#include "Connection.h"

Connection::Connection(boost::asio::io_service &io_service, string rootDir): socket(io_service), strand(io_service), request(rootDir), offset(0) {
    // todo TCP_CORK setsockopt
}

Connection::~Connection() {
   socket.close();
}

void Connection::start() {
    socket.non_blocking(true);
    socket.native_non_blocking(true);

    socket.async_read_some(
            boost::asio::buffer(buffer, bufferSize),
            strand.wrap(boost::bind(&Connection::handleRead, shared_from_this(),
                                    boost::asio::placeholders::error,
                                    boost::asio::placeholders::bytes_transferred))

    );
}

void Connection::handleRead(const boost::system::error_code &error_code, size_t size) {
    request.parseRequest(std::string(buffer), size,
                         std::bind(&Connection::sendMessage, shared_from_this(), std::placeholders::_1),
                         std::bind(&Connection::sendFile, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void Connection::handleWrite(const boost::system::error_code& error, std::size_t bytes_transferred) {

}

void Connection::sendMessage(const std::string &message) {
     socket.async_write_some(
             boost::asio::buffer(message, message.size()),
             strand.wrap(boost::bind(&Connection::handleWrite, shared_from_this(),
                                     boost::asio::placeholders::error,
                                     boost::asio::placeholders::bytes_transferred)
             )
     );
}

void Connection::sendFile(int fd, size_t size) {
//    sendfile(socket.native_handle(), fd, &offset, size);
    while (offset < size) {
        sendfile(socket.native_handle(), fd, &offset, 16384);
//        offset+=16384;
    }
    socket.async_write_some(boost::asio::null_buffers(), boost::bind(&Connection::handleWrite, shared_from_this(), _1, _2));
}

