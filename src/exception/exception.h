//
// Created by Wenner on 2020/1/17.
//

#ifndef KEESTO_EXCEPTION_H
#define KEESTO_EXCEPTION_H

#include <exception>
#include <iostream>
#include <cstring>


class exception {
private:
    char reason[50];
    char file[50];
    int line;
    char str[500];
public:
    exception(const char* file, int line, const char* reason){
        this->line = line;
        strcpy(this->file, file);
        strcpy(this->reason, reason);
    }
    ~exception() = default;

    const char* what(){
        strcpy(str, reason);
        strcat(str, " File:");
        strcat(str, file);
        strcat(str, " Line:");
        char s[6];
        int pos = 0;
        while(line){
            s[pos++] = 48 + line % 10;
            line /= 10;
        }
        s[pos] = '\0';
        strcat(str, s);
        return str;
    }
};


#endif //KEESTO_EXCEPTION_H
