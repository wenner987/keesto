//
// Created by Wenner on 2020/1/17.
//

#ifndef KEESTO_HTTPRESPONSE_H
#define KEESTO_HTTPRESPONSE_H


class WebServer;

class HttpResponse {
private:
    WebServer* web_server;
    void write_some(const char *some);
    int is_set_code;
public:

    HttpResponse(WebServer *web_server);

    void set_code(int code);

    void redirect(const char *url);

    void set_header(const char *header);

    void set_body(const char *body);
};


#endif //KEESTO_HTTPRESPONSE_H
