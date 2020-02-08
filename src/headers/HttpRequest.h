//
// Created by Wenner on 2020/1/17.
//

#ifndef KEESTO_HTTPREQUEST_H
#define KEESTO_HTTPREQUEST_H

#include <map>
#include "Define.h"

class HttpString;

class HttpRequest {
private:
    HTTP_METHOD method;
    std::map<HttpString*, HttpString*>* headers;
    std::map<HttpString*, HttpString*>* parameters;
    std::map<HttpString*, HttpString*>* cookies;
    char* url = nullptr;

    void get_headers_(char* msg);
    void get_method_(char* msg);
    void get_parameters_(char* msg);
    void get_cookies_();
    void get_url_(char* msg);

    void set_header_(HttpString* key, HttpString* value);
    void set_method_(const char* method);
    void set_parameter(HttpString* parameter_k, HttpString* parameter_v);
    void set_cookie(HttpString* cookie_k, HttpString* cookie_v);

public:
    HttpRequest(char *msg);
    ~HttpRequest();

    HttpString* get_parameter(HttpString name);
    HttpString* get_header(HttpString name);
    HttpString* get_cookie(HttpString name);
    HttpString get_url();
    HTTP_METHOD get_method();
};


#endif //KEESTO_HTTPREQUEST_H
