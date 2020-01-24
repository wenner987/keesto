//
// Created by Wenner on 2020/1/15.
//

#ifndef KEESTO_SOCKET_H
#define KEESTO_SOCKET_H

#include <boost/asio.hpp>

#include <memory>


class server_socket: public std::enable_shared_from_this<server_socket> {
private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor_;

    void do_read();
public:
    server_socket(const short port);
};


#endif //KEESTO_SOCKET_H
