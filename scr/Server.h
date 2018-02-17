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
    Server(boost::asio::io_service& io_service);

private:

    void startAccept();

    void handleAccept(Connection::pointer new_connection, const boost::system::error_code &error);

    tcp::acceptor acceptor;
};


#endif //HIGHLOAD_SERVER_H
