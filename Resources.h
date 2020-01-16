//
// Created by Wenner on 2020/1/14.
//

#ifndef KEESTO_RESOURCES_H
#define KEESTO_RESOURCES_H

#include <map>

#include "Define.h"


class Resources {
private:
    std::map<std::string, std::string> global_cnf;
    void read_conf(std::string path);

public:
    Resources();
    ~Resources();

    const char* getConfig(const char* name);
};


#endif //KEESTO_RESOURCES_H
