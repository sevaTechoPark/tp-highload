//
// Created by seva on 17.02.18.
//

#include "Server.h"

Server::Server(int port, string host, size_t threads): acceptor(io_service, tcp::endpoint(tcp::v4(), port)), rootDir(host), threadsCount(threads) {
//    startAccept();
}

void Server::start() {
    for (std::size_t i = 0; i < threadsCount; i++) {
        threads.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
        io_service.post(boost::bind(&Server::startAccept, this));
    }
    boost::this_thread::sleep( boost::posix_time::millisec(6000));
    std::cout << "Server start with " << threadsCount << " CPU" << std::endl;
    threads.join_all();
}

void Server::startAccept() {
    Connection::pointer newConnection = Connection::create(acceptor.get_io_service(), rootDir);

    acceptor.async_accept(
            newConnection->getSocket(),
            boost::bind(&Server::handleAccept, this, newConnection, boost::asio::placeholders::error)
    );
}

void Server::handleAccept(Connection::pointer new_connection, const boost::system::error_code &error) {

    if (!error) {
        new_connection->start();
    }

    startAccept();
}
