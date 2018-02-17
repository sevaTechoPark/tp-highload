//
// Created by seva on 17.02.18.
//

#include "Server.h"

Server::Server(boost::asio::io_service& io_service): acceptor(io_service, tcp::endpoint(tcp::v4(), 8000)) {
    startAccept();
}

void Server::startAccept() {

    Connection::pointer new_connection = Connection::create(acceptor.get_io_service());

    acceptor.async_accept(
            new_connection->getSocket(),
            boost::bind(&Server::handleAccept, this, new_connection,
            boost::asio::placeholders::error)
    );
}

void Server::handleAccept(Connection::pointer new_connection, const boost::system::error_code &error) {

    if (!error) {
        new_connection->start();
    }

    startAccept();
}
