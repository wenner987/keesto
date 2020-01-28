//
// Created by Wenner on 2020/1/17.
//

#ifndef KEESTO_ILLEGALACCESSEXCEPTION_H
#define KEESTO_ILLEGALACCESSEXCEPTION_H

#include "exception.h"

class IllegalAccessException: public exception{
public:
    IllegalAccessException(const char *file, int line) : exception(file, line, "Illegal access exception.") {}
};

#endif //KEESTO_ILLEGALACCESSEXCEPTION_H
