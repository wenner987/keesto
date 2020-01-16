//
// Created by Wenner on 2020/1/15.
//

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

#include "headers/Socket.h"

server_socket::server_socket(const short port):
acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)){
    do_read();
    io_context.run();
}

void server_socket::do_read() {
    acceptor_.async_accept(
            [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket){
                if (!ec){
                    // TODO new web_server
                    boost::array<char, 20480> buf;
                    socket.read_some(boost::asio::buffer(buf), ec);
                    if(!ec){
                        for(int i = 0;buf[i] != '\0';i++){
                            std::cout << buf[i];
                        }
                        std::cout << std::endl;
                    }
                }
                socket.close();
                do_read();
            });
}
