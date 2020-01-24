//
// Created by Wenner on 2020/1/14.
//

#ifndef KEESTO_UTILS_H
#define KEESTO_UTILS_H

#include <boost/shared_ptr.hpp>
#include "Resources.h"

enum HTTP_METHOD{
    HTTP_METHOD_GET = 1,
    HTTP_METHOD_POST,
    HTTP_METHOD_PUT,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_TRACE,
    HTTP_METHOD_OPTIONS
};

class Utils {
private:
    std::shared_ptr<Resources> resources;
public:
    Utils();

    static std::shared_ptr<Utils> utils;

    std::shared_ptr<Resources> getResources(){
        return this->resources;
    }
};


#endif //KEESTO_UTILS_H
