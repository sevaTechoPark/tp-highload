//
// Created by seva on 17.02.18.
//

#ifndef HIGHLOAD_CONNECTION_H
#define HIGHLOAD_CONNECTION_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Request.h"

using boost::asio::ip::tcp;

class Connection: public boost::enable_shared_from_this<Connection> {
public:
    typedef boost::shared_ptr<Connection> pointer;

    static pointer create(boost::asio::io_service& io_service) {
        return pointer(new Connection(io_service));
    }

    tcp::socket& getSocket() {
        return socket;
    };

    void start();


private:
    Connection(boost::asio::io_service& io_service);

    void handleRead(const boost::system::error_code &, size_t);

    void doWrite(const std::string &);

    tcp::socket socket;
    char buffer[1024];
    Request request;
};


#endif //HIGHLOAD_CONNECTION_H

