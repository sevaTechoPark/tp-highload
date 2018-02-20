//
// Created by seva on 17.02.18.
//

#include "Server.h"

Server::Server(int port, string host): acceptor(io_service, tcp::endpoint(boost::asio::ip::address::from_string(host), port)) {
    startAccept();
}

void Server::start() {
    for (std::size_t i = 0; i < 4; ++i) {
        boost::shared_ptr<boost::thread> thread(new boost::thread(boost::bind(&boost::asio::io_service::run, &io_service)));
        thread->join();
    }
    // io_service.run();
}

void Server::startAccept() {

    Connection::pointer newConnection = Connection::create(acceptor.get_io_service(), rootDir);

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
