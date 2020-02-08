//
// Created by Wenner on 2020/1/17.
//

#ifndef KEESTO_WEBSERVER_H
#define KEESTO_WEBSERVER_H


#include <boost/asio/ip/tcp.hpp>
#include <memory>

class HttpRequest;
class HttpResponse;
class HttpString;

class WebServer: public std::enable_shared_from_this<WebServer>{
private:
    boost::asio::ip::tcp::socket socket_;
    HttpRequest* http_request;
    HttpResponse* http_response;

    void read_message();
    void invoke(std::string path);
    void return_403();
    void return_static(std::string& path);
    void return_404();
    bool purview_check(std::string name);
public:
    WebServer(boost::asio::ip::tcp::socket socket);

    ~WebServer();

    void write_some(const HttpString response_string);

    void start();

};


#endif //KEESTO_WEBSERVER_H
