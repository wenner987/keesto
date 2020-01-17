//
// Created by Wenner on 2020/1/17.
//

#ifndef KEESTO_FILENOTFOUNDEXCEPTION_H
#define KEESTO_FILENOTFOUNDEXCEPTION_H

#include "exception.h"

class FileNotFoundException: public exception{
private:
    const char* reason = "File not found.";
};

#endif //KEESTO_FILENOTFOUNDEXCEPTION_H
