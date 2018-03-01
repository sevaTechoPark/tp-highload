//
// Created by seva on 17.02.18.
//

#ifndef HIGHLOAD_SERVER_H
#define HIGHLOAD_SERVER_H

#include "Connection.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

using boost::asio::ip::tcp;

class Server {
public:
    Server(int, std::string, size_t);

    void start();
private:

    void startAccept();

    void handleAccept(Connection::pointer new_connection, const boost::system::error_code &error);

    boost::asio::io_service io_service;
    tcp::acceptor acceptor;
    boost::thread_group threadPool;
    size_t threadsCount;
    string rootDir;
};


#endif //HIGHLOAD_SERVER_H
