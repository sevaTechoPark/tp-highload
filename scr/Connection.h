//
// Created by seva on 17.02.18.
//

#ifndef HIGHLOAD_CONNECTION_H
#define HIGHLOAD_CONNECTION_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

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

    void handleWrite(const boost::system::error_code &, size_t);

    tcp::socket socket;
    char buffer[1024];
};


#endif //HIGHLOAD_CONNECTION_H

