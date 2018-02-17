//
// Created by seva on 17.02.18.
//

#include "Server.h"

Server::Server(boost::asio::io_service& io_service): acceptor_(io_service, tcp::endpoint(tcp::v4(), 8000)) {
    start_accept();
}

void Server::start_accept() {

    Connection::pointer new_connection = Connection::create(acceptor_.get_io_service());

    acceptor_.async_accept(
            new_connection->socket(),
            boost::bind(&Server::handle_accept, this, new_connection,
            boost::asio::placeholders::error)
    );
}

void Server::handle_accept(Connection::pointer new_connection, const boost::system::error_code& error) {

    if (!error) {
        new_connection->start();
    }

    start_accept();
}
