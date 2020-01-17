// Created by Wenner on 2020/1/17.
//

#ifndef KEESTO_HTTPSTRING_H
#define KEESTO_HTTPSTRING_H

#include <cstddef>
#include <string>
#include <boost/exception/detail/shared_ptr.hpp>

class HttpString {
private:
    char* base;
    size_t capacity;

    bool add_space();
public:
    HttpString();
    HttpString(size_t size);
    HttpString(const HttpString& string);
    HttpString(const HttpString&& string);

    HttpString(std::string string);
    HttpString(const char* string);

    ~HttpString();

    const char* c_str();

    int length;

    HttpString* cat(HttpString rval);

    std::shared_ptr<HttpString> split(int start_pos, int end_pos);

};


#endif //KEESTO_HTTPSTRING_H
