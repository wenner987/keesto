//
// Created by Wenner on 2020/1/17.
//

#ifndef KEESTO_HTTPREQUEST_H
#define KEESTO_HTTPREQUEST_H

#include <map>

#include "HttpString.h"
#include "Utils.h"


class HttpRequest {
private:
    HTTP_METHOD method;
    std::map<std::shared_ptr<HttpString>, std::shared_ptr<HttpString>> headers;
    std::map<std::shared_ptr<HttpString>, std::shared_ptr<HttpString>> parameters;
    std::map<std::shared_ptr<HttpString>, std::shared_ptr<HttpString>> cookies;
    std::shared_ptr<char> url;

    void get_headers_(char* msg);
    void get_method_(char* msg);
    void get_parameters_(char* msg);
    void get_cookies_();
    void get_url_(char* msg);

    void set_header_(HttpString* key, HttpString* value);
    void set_method_(const char* method);
    void set_parameter(HttpString* parameter_k, HttpString* parameter_v);
    void set_cookie(HttpString cookie_k, HttpString cookie_v);

public:
    HttpRequest(char *msg);


    std::shared_ptr<HttpString> get_parameter(HttpString name);
    std::shared_ptr<HttpString> get_header(HttpString name);
    std::shared_ptr<HttpString> get_cookie(HttpString name);
    std::shared_ptr<HttpString> get_url();
    HTTP_METHOD get_method();
};


#endif //KEESTO_HTTPREQUEST_H
