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
    Server(boost::asio::io_service& io_service): acceptor_(io_service, tcp::endpoint(tcp::v4(), 8000)) {
        start_accept();
    }

private:

    void start_accept();

    void handle_accept(Connection::pointer new_connection, const boost::system::error_code& error);

    tcp::acceptor acceptor_;
};


#endif //HIGHLOAD_SERVER_H
