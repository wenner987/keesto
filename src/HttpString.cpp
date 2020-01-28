//
// Created by Wenner on 2020/1/17.
//

#include "headers/HttpString.h"
#include "exception/IllegalAccessException.h"

#include <cstring>
#include <iostream>

HttpString::HttpString(){
    base = nullptr;
    length = capacity = 0;
}

HttpString::HttpString(size_t size){
    base = new char[size + 5];
    length = 0;
    capacity = size + 3;
}

HttpString::HttpString(const HttpString& string){
    base = new char[string.length];
    length = capacity = string.length;
    memcpy(base, string.base, string.length * sizeof(char) + 1);
}

HttpString::HttpString(std::string string){
    base = new char[string.size() + 5];
    length = string.size();
    capacity = length + 5;
    memcpy(base, string.c_str(), string.size());
}

HttpString::HttpString(const char* string){
    capacity = length = strlen(string);
    if(length != 0)
        base = new char[length];
    memcpy(base, string, sizeof(char) * length);
}

const char * HttpString::c_str() const {
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

HttpString* HttpString::cat(char rval){
    while(this->capacity < 1 + this->length){
        add_space();
    }
    this->base[this->length++] = rval;
    this->base[this->length] = '\0';
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

void HttpString::strip(char ch){
    int start_pos = 0, end_pos = length - 1;
    if(ch == '\0'){
        while((base[end_pos] == ' ' || base[end_pos] == '\n') && start_pos < end_pos) end_pos--;
        while((base[start_pos] == ' ' || base[start_pos] == '\n') && start_pos < end_pos) start_pos++;
    }
    else {
        while(base[end_pos--] == ch && start_pos < end_pos);
        while(base[start_pos++] == ch && start_pos < end_pos);
    }
    char* new_space = new char[end_pos - start_pos];
    length = 0;
    capacity = end_pos - start_pos;
    for(int i = start_pos;i <= end_pos;i++){
        new_space[length++] = base[i];
    }
    delete[] base;
    base = new_space;
    return;
}

HttpString HttpString::operator=(HttpString value){
    this->length = value.length;
    this->capacity = value.capacity;
    this->base = new char[this->capacity];
    strcpy(this->base, value.base);
}

int HttpString::operator<(const HttpString& value)const{
    return strcmp(this->base, value.base);
}

void HttpString::reset(){
    this->length = 0;
    this->base[0] = '\0';
}
