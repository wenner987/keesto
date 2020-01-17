//
// Created by Wenner on 2020/1/17.
//

#ifndef KEESTO_WEBSERVER_H
#define KEESTO_WEBSERVER_H


#include <boost/asio/ip/tcp.hpp>

class WebServer {
private:
    boost::asio::ip::tcp::socket socket_;
public:
    WebServer(boost::asio::ip::tcp::socket socket);
};


#endif //KEESTO_WEBSERVER_H
