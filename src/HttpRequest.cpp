//
// Created by Wenner on 2020/1/17.
//

#include "headers/HttpRequest.h"

#include <cstring>
#include <iostream>

void HttpRequest::get_headers_(char* msg){
    while(*msg != '\n') msg++;
    msg++;
    bool is_key = true;
    HttpString key(30);
    HttpString value(300);
    for(int i = 0;msg[i] != '\0';i++){
        if(msg[i] == ':' && is_key){
            is_key = false;
        }
        else if(msg[i] == '\n'){
            key.strip();
            value.strip();
            set_header_(new HttpString{key}, new HttpString{value});
            key.reset();
            value.reset();
            is_key = true;
        }
        else if(msg[i] != ' '){
            is_key ? key.cat(msg[i]) : value.cat(msg[i]);
        }
    }
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
        while(*msg != '?' && *msg != '\0') msg++;
        if(*msg == '\0') return;
        msg++;
        int len = 0;
        while(*msg != ' '){
            parameter[len++] = *msg;
            msg++;
        }
        parameter[len] = '\0';
        std::shared_ptr<char> para_dec = Utils::utils->url_decode(parameter);
        HttpString key(256);
        HttpString value(4096);
        bool is_key = true;
        for(int i = 0;para_dec.get()[i] != '\0';i++){
            if(para_dec.get()[i] == '&' || para_dec.get()[i] == '\0'){
                set_parameter(new HttpString{key}, new HttpString{value});
                key.reset();
                value.reset();
                is_key = true;
            }
            else if(para_dec.get()[i] == '='){
                is_key = false;
            }
            else{
                if(is_key){
                    key.cat(para_dec.get()[i]);
                }
                else{
                    value.cat(para_dec.get()[i]);
                }
            }
        }
        delete[] parameter;
        set_parameter(new HttpString{key}, new HttpString{value});
    }
    else{

    }
}
void HttpRequest::get_cookies_(){
    HttpString* cookie = get_header("Cookie");
    if(cookie == nullptr) return;
    for(auto iter: *this->headers){
        if(!(strcmp(iter.first->c_str(), "Cookie"))){
            this->headers->erase(iter.first);
            delete iter.first;
            break;
        }
    }
    bool is_key = true;
    HttpString key{64}, value{64};
    for(int i = 0;i < cookie->length;i++){
        if(cookie->c_str()[i] == '='){
            is_key = false;
        }
        else if(cookie->c_str()[i] == ';'){
            set_cookie(
                    new HttpString{Utils::utils->url_decode(key.c_str()).get()},
                    new HttpString{Utils::utils->url_decode(value.c_str()).get()});
        }
        else{
            is_key ? key.cat(cookie->c_str()[i]) : value.cat(cookie->c_str()[i]);
        }
    }
    delete cookie;
}

void HttpRequest::set_header_(HttpString* key, HttpString* value){
    (*this->headers)[key] = value;
}

void HttpRequest::set_method_(const char* method){
    Utils::set_method(method, &this->method);
}

void HttpRequest::set_parameter(HttpString* parameter_k, HttpString* parameter_v){
    (*this->parameters)[parameter_k] = parameter_v;
}

void HttpRequest::set_cookie(HttpString* cookie_k, HttpString* cookie_v){
    (*this->cookies)[cookie_k] = cookie_v;
}


HttpString* HttpRequest::get_parameter(HttpString name){
    for(auto iter: *this->parameters){
        if(strcmp(iter.first->c_str(), name.c_str()) == 0){
            return iter.second;
        }
    }
    return nullptr;
}

HttpString* HttpRequest::get_header(HttpString name){
    for(auto iter: *this->headers){
        if(strcmp(iter.first->c_str(), name.c_str()) == 0){
            return iter.second;
        }
    }
    return nullptr;
}

HttpString* HttpRequest::get_cookie(HttpString name){
    for(auto iter: *this->cookies){
        if(strcmp(iter.first->c_str(), name.c_str()) == 0){
            return iter.second;
        }
    }
    return nullptr;
}
HTTP_METHOD HttpRequest::get_method(){
    return this->method;
}

HttpRequest::HttpRequest(char* msg){
    headers = new std::map<HttpString*, HttpString*>{};
    parameters = new std::map<HttpString*, HttpString*>{};
    cookies = new std::map<HttpString*, HttpString*>{};
    url = new char[2048];
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
    strcpy(url, Utils::utils->url_decode(uri).get());
    delete[] uri;
}

HttpString HttpRequest::get_url(){
    return this->url;
}

void field_delete(std::map<HttpString*, HttpString*>* val){
    for(auto iter: *val){
        delete iter.second;
        val->erase(iter.first);
        delete iter.first;
    }
}

HttpRequest::~HttpRequest(){
    if(headers != nullptr){
        field_delete(headers);
        delete this->headers;
        headers = nullptr;
    }
    if(parameters != nullptr){
        field_delete(parameters);
        delete this->parameters;
        parameters = nullptr;
    }
    if(cookies != nullptr){
        field_delete(cookies);
        delete this->cookies;
        cookies = nullptr;
    }
    if(this->url != nullptr){
        delete[] url;
        this->url = nullptr;
    }
}
