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

    char hex_2_char(const char* hex);
public:
    Utils();

    static std::shared_ptr<Utils> utils;

    std::shared_ptr<Resources> get_resources();

    std::shared_ptr<char>url_decode(const char* src);
};


#endif //KEESTO_UTILS_H
