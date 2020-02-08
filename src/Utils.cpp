//
// Created by Wenner on 2020/1/14.
//

#include <execinfo.h>
#include <cstring>
#include <dlfcn.h>
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>

#include "headers/Utils.h"
#include "headers/HttpResponse.h"
#include "headers/Mapper.h"
#include "headers/MapperEntity.h"
#include "headers/Resources.h"


std::shared_ptr<Utils> Utils::utils = std::make_shared<Utils>();

Utils::Utils(){
    this->resources = std::make_shared<Resources>();
    this->mapper = nullptr;
}

std::shared_ptr<Resources> Utils::get_resources() {
    return this->resources;
}

std::shared_ptr<Mapper> Utils::load_mapper(){
    if(this->mapper == nullptr)
        this->mapper = std::make_shared<Mapper>();
    return this->mapper;
}


std::shared_ptr<char> Utils::url_decode(const char* src) {
    if(*src == 0) return nullptr;
    char* res = new char[1024];
    int len = 0;
    char ch;
    while(*src != '\0'){
        if(*src == '%'){
            ch = hex_2_char(src + 1);
            src += 2;
        }
        else{
            ch = *src;
        }
        res[len++] = ch;
        src++;
    }
    res[len] = '\0';
    return std::shared_ptr<char>(res);
}

char Utils::hex_2_char(const char* hex){
    char str[5] = {0};
    char ch;
    str[0] = hex[0];
    str[1] = hex[1];
    str[2] = '\0';
    sscanf(str, "%x", &ch);
    return ch;
}

void Utils::single_handler(int sig){
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr,"Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(20);
}

void Utils::set_method(const char* src, HTTP_METHOD* dst){
    if(strcmp(src, "GET") == 0){
        *dst = HTTP_METHOD_GET;
    }
    else if(strcmp(src, "POST") == 0){
        *dst = HTTP_METHOD_POST;
    }
    else if(strcmp(src, "DELETE") == 0){
        *dst = HTTP_METHOD_DELETE;
    }
    else if(strcmp(src, "PUT") == 0){
        *dst = HTTP_METHOD_PUT;
    }
    else if(strcmp(src, "HEAD") == 0){
        *dst = HTTP_METHOD_HEAD;
    }
    else if(strcmp(src, "TRACE")){
        *dst = HTTP_METHOD_TRACE;
    }
    else if(strcmp(src, "OPTIONS")){
        *dst = HTTP_METHOD_OPTIONS;
    }
    else {
        *dst = HTTP_INVALID;
    }
}

Utils::handler Utils::get_handler(const char* name){
    if(this->handlers[name] == nullptr && this->load_mapper()->get_mapper(name) != nullptr){
        std::string location = this->load_mapper()->get_mapper(name)->location;
        std::string dynamic_library = this->load_mapper()->get_mapper(name)->dynamic_library;
        std::cout << location + dynamic_library << std::endl;
        if(!boost::filesystem::exists(location + dynamic_library)){
            return nullptr;
        }
        if(this->dynamic_library[location + dynamic_library] == nullptr)
            this->dynamic_library[location + dynamic_library] = dlopen(
                    (location + dynamic_library).c_str(), RTLD_NOW);
        this->handlers[name] = reinterpret_cast<Utils::handler>(
                dlsym(this->dynamic_library[location + dynamic_library],
                        this->load_mapper()->get_mapper(name)->function_name.c_str()));
    }
    return this->handlers[name];
}
