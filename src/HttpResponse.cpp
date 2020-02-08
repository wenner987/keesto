//
// Created by Wenner on 2020/1/17.
//

#include "headers/HttpResponse.h"
#include "headers/WebServer.h"
#include "headers/HttpString.h"

void HttpResponse::set_code(int code){
    char* str = new char[128];
    strcpy(str, "HTTP/1.1 ");
    strcat(str, std::to_string(code).c_str());
    this->is_set_code = 1;
    switch (code){
        case 403:{
            strcat(str, " Forbidden");
            break;
        }
        case 404:{
            strcat(str, " Not Found");
            break;
        }
        case 302:{
            strcat(str, " Move Temporarily");
        }
        default:{
            strcat(str, " OK");
        }
    }
    strcat(str, "\n");
    this->write_some(str);
    delete[] str;
}

HttpResponse::HttpResponse(WebServer* web_server): web_server(web_server){
    this->is_set_code = 0;
}

void HttpResponse::redirect(const char* url){
    this->set_code(302);
    char* str = new char[256];
    strcpy(str, "Location: ");
    strcat(str, url);
    this->write_some(str);
    delete[] str;
}

void HttpResponse::set_header(const char* header){
    char* str = new char[1024];
    strcpy(str, header);
    strcat(str, "\n");
    this->write_some(str);
    delete[] str;
}

void HttpResponse::write_some(const char* some){
    this->web_server->write_some(some);
}

void HttpResponse::set_body(const char* body){
    if(!is_set_code){
        set_code(200);
    }
    this->write_some("\n");
    this->write_some(body);
}
