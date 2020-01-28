//
// Created by Wenner on 2020/1/14.
//

#include "headers/Utils.h"

std::shared_ptr<Utils> Utils::utils = std::make_shared<Utils>();

Utils::Utils(){
    this->resources = std::make_shared<Resources>();
}

std::shared_ptr<Resources> Utils::get_resources() {
    return this->resources;
}

std::shared_ptr<char> Utils::url_decode(const char* src) {
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