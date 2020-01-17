//
// Created by Wenner on 2020/1/17.
//

#include "headers/HttpString.h"

#include <cstring>
#include <iostream>
#include <boost/assert.hpp>

#include "exception/IllegalAccessException.h"


HttpString::HttpString(){
    base = nullptr;
    length = capacity = 0;
}
HttpString::HttpString(size_t size){
    base = new char[size + 5];
    length = capacity = 0;
}
HttpString::HttpString(const HttpString& string){
    base = new char[string.length];
    length = capacity = string.length;
    memcpy(base, string.base, string.length * sizeof(char));
}

HttpString::HttpString(std::string string){
    base = new char[string.size() + 5];
    length = string.size();
    capacity = length + 5;
    memcpy(base, string.c_str(), string.size());
}
HttpString::HttpString(const char* string){
    capacity = length = strlen(string);
    base = new char[length];
    memcpy(base, string, sizeof(char) * length);
}

const char * HttpString::c_str() {
    return this -> base;
}

HttpString* HttpString::cat(HttpString rval){
    while(this->capacity < rval.length + this->length){
        add_space();
    }
    memcpy(this->base + this->length * sizeof(char), rval.base, rval.length * sizeof(char));
    this->length += rval.length;
    return this;
}

bool HttpString::add_space(){
    if(this->capacity == 0){
        this->capacity = 1;
    }
    try{
        char *new_space = new char[this->capacity*2];
        this->capacity *= 2;
        memcpy(new_space, this->base, length * sizeof(char));
        char* old = this->base;
        this->base = new_space;
        if(this->base)
            delete[] old;
        return true;
    }
    catch(std::bad_alloc& e){
        std::cerr << e.what() << std::endl;
    }
}

HttpString::~HttpString(){
    if(this->base)
        delete[] this->base;
}

std::shared_ptr<HttpString> HttpString::split(int start_pos, int end_pos){
    if(start_pos < 0 || end_pos > length || end_pos < start_pos){
        throw IllegalAccessException{__FILE__, __LINE__};
    }
    else{
        std::shared_ptr<HttpString> res = std::make_shared<HttpString>
                (static_cast<size_t>(end_pos - start_pos + 1));
        for(int i = start_pos;i < end_pos;i++){
            res->base[res->length++] = this->base[i];
        }
        res->base[res->length] = '\0';
        return res;
    }
}
