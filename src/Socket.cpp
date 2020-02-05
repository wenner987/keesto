//
// Created by Wenner on 2020/1/15.
//

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
                    WebServer* web_server = new WebServer{std::move(socket)};
                    web_server->start();
                    delete web_server;
                }
                socket.close();
                do_read();
            });
}
