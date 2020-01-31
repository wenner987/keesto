//
// Created by Wenner on 2020/1/17.
//

#ifndef KEESTO_WEBSERVER_H
#define KEESTO_WEBSERVER_H


#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include "HttpRequest.h"
#include "HttpResponse.h"

class WebServer: public std::enable_shared_from_this<WebServer>{
private:
    boost::asio::ip::tcp::socket socket_;
    HttpRequest* http_request;
    HttpResponse* http_response;

    void read_message();

    void invoke();

public:
    WebServer(boost::asio::ip::tcp::socket socket);

    ~WebServer();

    void write_some(const HttpString response_string);

    void start();
};


#endif //KEESTO_WEBSERVER_H
