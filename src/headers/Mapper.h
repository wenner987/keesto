//
// Created by Wenner on 2020/2/4.
//

#ifndef KEESTO_MAPPER_H
#define KEESTO_MAPPER_H

#include <map>

class MapperEntity;

class Mapper{
private:
    bool use_mysql = false;
    std::map<std::string, std::string*> global;
    std::map<std::string, MapperEntity*> mapper;
public:
    Mapper();
    ~Mapper();

    void read_mapper(const std::string& path);
    MapperEntity* get_mapper(std::string name);
    std::string* get_global(std::string name);
};

#endif //KEESTO_MAPPER_H
