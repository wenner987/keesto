//
// Created by Wenner on 2020/1/17.
//

#include "headers/WebServer.h"
#include "headers/HttpRequest.h"

#include <boost/array.hpp>
#include <iostream>
#include <boost/bind.hpp>

WebServer::WebServer(boost::asio::ip::tcp::socket socket):
    socket_(std::move(socket)){}

void WebServer::start(){
    read_message();
}

void WebServer::read_message() {
    boost::array<char, 10240> buf;
    boost::system::error_code err;
    socket_.read_some(boost::asio::buffer(buf), err);

    if(!err){
        http_request = new HttpRequest(buf.c_array());
//        http_request = std::make_shared<HttpResponse>();
    }
    else{
        std::cerr << err.message() << std::endl;
    }
    if(buf[0] == 0) return;
    socket_.write_some(boost::asio::buffer(
            "HTTP/1.1 404 OK\n"
            "content-type: text/html; charset=utf-8\n\n"
            "<h1>hello</h1>\n"
            ));

    if(socket_.is_open()){
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_type::shutdown_both);
        socket_.close();
    }
}

void WebServer::write_some(const HttpString response_string){
    boost::array<char, 10240> response;
    for(int i = 0;response_string.c_str()[i] != '\0';i++){
        response[i] = response_string.c_str()[i];
    }
    try{
        this->socket_.write_some(boost::asio::buffer(response, response_string.length));
    }
    catch (...){}
}

WebServer::~WebServer(){
    delete this->http_response;
    delete this->http_request;
}
