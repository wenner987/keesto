//
// Created by Wenner on 2020/1/15.
//

#ifndef KEESTO_SOCKET_H
#define KEESTO_SOCKET_H

#include <boost/asio.hpp>


class Socket {
private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::acceptor acceptor;

    void do_read();
public:
    Socket(const short port);
};


#endif //KEESTO_SOCKET_H
