//
// Created by Wenner on 2020/1/17.
//

#include "headers/HttpRequest.h"

#include <cstdio>
#include <cstring>
#include <iostream>

void HttpRequest::get_headers_(char* msg){
    char* header = msg;
    while(*header != '\n') header++;
    header++;
    int len = strlen(header);
    bool is_key = true;
    for(int i = 0;i < len;i++){
        HttpString* key = new HttpString(10);
        HttpString* value = new HttpString(30);
        if(header[i] == '\r') continue;
        if(header[i] == '\n'){
            set_header_(key, value);
            is_key = true;
            i++;
        }
        else if(header[i] == ':' && is_key){
            i++;
            is_key = false;
        }
        if(is_key){
            key->cat(header[i]);
        }
        else{
            value->cat(header[i]);
        }
    }
}
void HttpRequest::get_method_(char* msg){
    this->method = HTTP_METHOD_POST;
    char* method = new char[10];
    for(int i = 0;msg[i] != ' ';i++){
        method[i] = msg[i];
        method[i + i] = '\0';
    }
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
    delete[] method;
}
void HttpRequest::get_parameters_(char* msg){

}
void HttpRequest::get_cookies_(char* msg){

}

void HttpRequest::set_header_(HttpString* key, HttpString* value){
    this->headers[std::shared_ptr<HttpString>{key}] = std::shared_ptr<HttpString>{value};
}

void HttpRequest::set_method_(HTTP_METHOD method){

}

void HttpRequest::set_parameter(HttpString parameter_k, HttpString parameter_v){

}
void HttpRequest::set_cookie(HttpString cookie_k, HttpString cookie_v){

}


std::shared_ptr<HttpString> HttpRequest::get_parameter(HttpString name){

}
std::shared_ptr<HttpString> HttpRequest::get_header(HttpString name){

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
    get_cookies_(msg);
}

void HttpRequest::get_url_(char *msg) {
    url.reset(new char[2048]);
    while(*msg != ' ') msg++;
    for(int i = 0;msg[i] != ' ';i++) {
        url.get()[i] = msg[i];
        url.get()[i + 1] = ' ';
    }
}

std::shared_ptr<HttpString> HttpRequest::get_url(){
    return std::make_shared<HttpString>(this->url.get());
}
