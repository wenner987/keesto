//
// Created by Wenner on 2020/1/14.
//

#ifndef KEESTO_UTILS_H
#define KEESTO_UTILS_H

#include <boost/shared_ptr.hpp>
#include <map>
#include "Define.h"

class HttpRequest;
class HttpResponse;
class Resources;
class Mapper;

class Utils {
private:
    typedef void (*handler)(HttpRequest*, HttpResponse*);

    std::shared_ptr<Resources> resources;

    std::shared_ptr<Mapper> mapper;

    std::map<std::string, handler> handlers;

    std::map<std::string, void*> dynamic_library;

    char hex_2_char(const char* hex);

public:
    Utils();

    static std::shared_ptr<Utils> utils;

    std::shared_ptr<Resources> get_resources();

    std::shared_ptr<Mapper> load_mapper();

    std::shared_ptr<char>url_decode(const char* src);

    static void single_handler(int sig);

    static void set_method(const char* src, HTTP_METHOD* dst);

    handler get_handler(const char* name);
};


#endif //KEESTO_UTILS_H
