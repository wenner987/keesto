//
// Created by Wenner on 2020/1/17.
//

#include "headers/HttpRequest.h"

#include <cstring>
#include <iostream>

// TODO write it tomorrow.
void HttpRequest::get_headers_(char* msg){
    char* header = msg;
    while(*header != '\n') header++;
    header++;
    int len = strlen(header);
    bool is_key = true;
    HttpString* key = new HttpString(10);
    HttpString* value = new HttpString(30);

    delete value;
    delete key;
}
void HttpRequest::get_method_(char* msg){
    char* method = new char[10];
    for(int i = 0;msg[i] != ' ';i++){
        method[i] = msg[i];
        method[i + 1] = '\0';
    }
    set_method_(method);
    delete[] method;
}
void HttpRequest::get_parameters_(char* msg){
    if(this->method == HTTP_METHOD_GET){
        char *parameter = new char[1024];
        while(*msg != '?') msg++;
        msg++;
        int len = 0;
        while(*msg != ' '){
            parameter[len++] = *msg;
            msg++;
        }
        parameter[len] = '\0';
        std::shared_ptr<char> para_dec = Utils::utils->url_decode(parameter);
        HttpString* key = new HttpString(256);
        HttpString* value = new HttpString(4096);
        bool is_key = true;
        for(int i = 0;para_dec.get()[i] != '\0';i++){
            if(para_dec.get()[i] == '&' || para_dec.get()[i] == '\0'){
                set_parameter(key, value);
                key = new HttpString(256);
                value = new HttpString(4096);
                is_key = true;
            }
            else if(para_dec.get()[i] == '='){
                is_key = false;
            }
            else{
                if(is_key){
                    key->cat(para_dec.get()[i]);
                }
                else{
                    value->cat(para_dec.get()[i]);
                }
            }
        }
        delete[] parameter;
        set_parameter(key, value);
    }
    else{

    }
}
void HttpRequest::get_cookies_(){
//    for(auto iter: this->headers){
//        std::cout << iter.first->c_str() << "   " << iter.second->c_str() << std::endl;
//    }
//    std::cout << this->get_header("Cookie")->c_str() << std::endl;
}

void HttpRequest::set_header_(HttpString* key, HttpString* value){
    this->headers[std::shared_ptr<HttpString>{key}] = std::shared_ptr<HttpString>{value};
}

void HttpRequest::set_method_(const char* method){
    if(strcmp(method, "GET") == 0){
        this->method = HTTP_METHOD_GET;
    }
    else if(strcmp(method, "POST") == 0){
        this->method = HTTP_METHOD_POST;
    }
    else if(strcmp(method, "DELETE") == 0){
        this->method = HTTP_METHOD_DELETE;
    }
    else if(strcmp(method, "PUT") == 0){
        this->method = HTTP_METHOD_PUT;
    }
    else if(strcmp(method, "HEAD") == 0){
        this->method = HTTP_METHOD_HEAD;
    }
    else if(strcmp(method, "TRACE")){
        this->method = HTTP_METHOD_TRACE;
    }
    else{
        this->method = HTTP_METHOD_OPTIONS;
    }
}

void HttpRequest::set_parameter(HttpString* parameter_k, HttpString* parameter_v){
    this->parameters[std::shared_ptr<HttpString>(parameter_k)] = std::shared_ptr<HttpString>(parameter_v);
}
void HttpRequest::set_cookie(HttpString cookie_k, HttpString cookie_v){

}


std::shared_ptr<HttpString> HttpRequest::get_parameter(HttpString name){

}
std::shared_ptr<HttpString> HttpRequest::get_header(HttpString name){
    for(auto iter: this->headers){
        if(strcmp(iter.first->c_str(), name.c_str())){
            return iter.second;
        }
    }
}
std::shared_ptr<HttpString> HttpRequest::get_cookie(HttpString name){

}
HTTP_METHOD HttpRequest::get_method(){

}

HttpRequest::HttpRequest(char* msg){
    get_method_(msg);
    get_url_(msg);
    get_headers_(msg);
    get_parameters_(msg);
    get_cookies_();
}

void HttpRequest::get_url_(char *msg) {
    char* uri = new char[1024];
    int len = 0;
    while(*msg != ' ') msg++;
    msg++;
    while(*msg != ' ' && *msg != '?'){
        uri[len++] = *msg;
        msg++;
    }
    uri[len] = '\0';
    url = Utils::utils->url_decode(uri);
    delete[] uri;
}

std::shared_ptr<HttpString> HttpRequest::get_url(){
    return std::make_shared<HttpString>(this->url.get());
}
