//
// Created by Wenner on 2020/2/4.
//

#ifndef KEESTO_MAPPERENTITY_H
#define KEESTO_MAPPERENTITY_H

#include <string>
#include "Define.h"

class MapperEntity{
public:
    std::string location;
    std::string dynamic_library;
    std::string function_name;
    HTTP_METHOD method;
    MapperEntity() {
        this->location = "invalid";
        this->dynamic_library = "invalid";
        this->function_name = "invalid";
        this->method = HTTP_INVALID;
    }
};

#endif //KEESTO_MAPPERENTITY_H
