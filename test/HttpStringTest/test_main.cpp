//
// Created by Wenner on 2020/1/17.
//

#include <iostream>

#include "../../src/headers/HttpString.h"
#include "../../src/exception/IllegalAccessException.h"

int main(int argc, char** argv){
    HttpString* str = new HttpString("xxadasd");

    std::cout << str->c_str() << std::endl;

    std::cout << str->length << std::endl;

    std::cout << str->length << std::endl;

    str->cat("sss")->cat("ssx")->cat("ab")->cat(std::string("sss"));

    std::cout << str->c_str() << std::endl;

    std::cout << str->split(1, 5)->c_str() << std::endl;

    try{
        std::cout << str->split(5, 1)->c_str() << std::endl;
    }
    catch (IllegalAccessException& e){
        std::cout << 1 << std::endl;
        std::cout << e.what() << std::endl;
    }

    return 0;
}
