//
// Created by Wenner on 2020/1/17.
//

#include "headers/WebServer.h"

WebServer::WebServer(boost::asio::ip::tcp::socket socket):
    socket_(std::move(socket)){

}

