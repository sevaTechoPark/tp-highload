//
// Created by seva on 17.02.18.
//

#ifndef HIGHLOAD_SERVER_H
#define HIGHLOAD_SERVER_H

#include "Connection.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

class Server {
public:
    Server(int port, std::string);

    void start();
private:

    void startAccept();

    void handleAccept(Connection::pointer new_connection, const boost::system::error_code &error);

    boost::asio::io_service io_service;
    tcp::acceptor acceptor;

    string rootDir = "/home/seva/dev/technopark/http-test-suite";
};


#endif //HIGHLOAD_SERVER_H
