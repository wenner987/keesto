//
// Created by Wenner on 2020/1/15.
//

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

#include "headers/Socket.h"
#include "headers/WebServer.h"

server_socket::server_socket(const short port):
acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)){
    do_read();
    io_context.run();
}

void server_socket::do_read() {
    acceptor_.async_accept(
            [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket){
                if (!ec){
                    std::shared_ptr<WebServer> server = std::make_shared<WebServer>(std::move(socket));
                    server->start();
                }
                socket.close();
                do_read();
            });
}
