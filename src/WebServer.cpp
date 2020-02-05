//
// Created by Wenner on 2020/1/17.
//

#include "headers/WebServer.h"
#include "headers/HttpRequest.h"

#include <boost/array.hpp>
#include <iostream>
#include <boost/bind.hpp>
#include <fstream>
#include <boost/filesystem.hpp>

WebServer::WebServer(boost::asio::ip::tcp::socket socket):
    socket_(std::move(socket)){}

void WebServer::start(){
    read_message();
//    invoke();
}

void WebServer::read_message(){
    boost::array<char, 10240> buf{};
    boost::system::error_code err;
    socket_.read_some(boost::asio::buffer(buf), err);

    if(!err){
        http_request = new HttpRequest(buf.c_array());
        http_response = new HttpResponse();
    }
    else{
        std::cerr << err.message() << std::endl;
    }

    if(buf[0] == 0) return;

    this->invoke(http_request->get_url().c_str());
}

void WebServer::write_some(const HttpString& response_string){
    try{
        this->socket_.write_some(boost::asio::buffer(response_string.c_str(), response_string.length));
    }
    catch (...){}
}

WebServer::~WebServer(){
    delete this->http_response;
    delete this->http_request;
}

bool WebServer::purview_check(std::string name) {
    MapperEntity* mapper = Utils::utils->load_mapper()->get_mapper(name);
    return (mapper == nullptr && this->http_request->get_method() == HTTP_METHOD_GET)
           || (mapper->method == this->http_request->get_method());
}

void WebServer::invoke(std::string path) {
    if(!purview_check(path)){
        this->return_403();
    }else {
        void (*handler)(HttpRequest*, HttpResponse*);
        handler = Utils::utils->get_handler(path.c_str());
        if(handler == nullptr){
            path = Utils::utils->get_resources()->get_config("RootDoc") + path;
            if(boost::filesystem::exists(path)){
                return_static(path);
            }
            else{
                return_404();
            }
        }else {
            handler(http_request, http_response);
        }
    }
}

void WebServer::return_403() {
    this->write_some("HTTP/1.1 403 Forbidden\n\n");
    std::string* path = Utils::utils->load_mapper()->get_global("403_page");
    std::ifstream* t = new std::ifstream{*path};

    this->write_some(std::string((std::istreambuf_iterator<char>(*t)),
            std::istreambuf_iterator<char>()) );
    delete t;
}

void WebServer::return_static(std::string& path){
    this->write_some("HTTP/1.1 200 OK\n\n");
    std::ifstream* t = new std::ifstream{path};
    this->write_some(std::string((std::istreambuf_iterator<char>(*t)),
                                 std::istreambuf_iterator<char>()) );
}

void WebServer::return_404(){
    this->write_some("HTTP/1.1 404 Not Found\n\n");
    std::string* path = Utils::utils->load_mapper()->get_global("404_page");
    std::ifstream* t = new std::ifstream{*path};

    this->write_some(std::string((std::istreambuf_iterator<char>(*t)),
                                 std::istreambuf_iterator<char>()) );
    delete t;
}