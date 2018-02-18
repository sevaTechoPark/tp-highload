//
// Created by seva on 17.02.18.
//

#include "Server.h"

Server::Server(int port): acceptor(io_service, tcp::endpoint(tcp::v4(), port)) {
    startAccept();
}

void Server::start() {
    io_service.run();
}

void Server::startAccept() {

    Connection::pointer newConnection = Connection::create(acceptor.get_io_service());

    acceptor.async_accept(
            newConnection->getSocket(),
            boost::bind(&Server::handleAccept, this, newConnection,
            boost::asio::placeholders::error)
    );
}

void Server::handleAccept(Connection::pointer new_connection, const boost::system::error_code &error) {

    if (!error) {
        new_connection->start();
    }

    startAccept();
}
