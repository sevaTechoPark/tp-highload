//
// Created by seva on 17.02.18.
//

#include "Server.h"

Server::Server(int port, string host, size_t threads): acceptor(io_service, tcp::endpoint(tcp::v4(), port)), rootDir(host), threadsCount(threads) {
    startAccept();
}

void Server::start() {
    std::cout << "Server start with " << threadsCount << " CPU" << std::endl;
    std::vector<boost::shared_ptr<boost::thread> > threads;
    for (std::size_t i = 0; i < threadsCount; ++i)
    {
        boost::shared_ptr<boost::thread> thread(new boost::thread(
                boost::bind(&boost::asio::io_service::run, &io_service)));
        threads.push_back(thread);
    }

    // Wait for all threads in the pool to exit.
    for (std::size_t i = 0; i < threads.size(); ++i)
        threads[i]->join();
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
