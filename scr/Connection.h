//
// Created by seva on 17.02.18.
//

#ifndef HIGHLOAD_CONNECTION_H
#define HIGHLOAD_CONNECTION_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <sys/sendfile.h>
#include "Request.h"

using boost::asio::ip::tcp;

class Connection: public boost::enable_shared_from_this<Connection> {
public:
    typedef boost::shared_ptr<Connection> pointer;

    static pointer create(boost::asio::io_service& io_service, string rootDir) {
        return pointer(new Connection(io_service, rootDir));
    }

    tcp::socket& getSocket() {
        return socket;
    };

    void start();


private:
    Connection(boost::asio::io_service &, string);

    void handleRead(const boost::system::error_code &, size_t);

    void handleWrite(const boost::system::error_code &, size_t);

    void sendMessage(const std::string &);

    void sendFile(int, size_t);

    tcp::socket socket;

    static const size_t bufferSize = 1024;
    char buffer[bufferSize];

    Request request;
    boost::asio::io_service::strand strand;

};


#endif //HIGHLOAD_CONNECTION_H

