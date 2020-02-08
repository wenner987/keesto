//
// Created by Wenner on 2020/2/4.
//

#include "headers/Mapper.h"
#include "headers/Utils.h"
#include "headers/MapperEntity.h"
#include "headers/Resources.h"

#include <cstring>

#include <boost/property_tree/ini_parser.hpp>

Mapper::~Mapper(){
    for(auto iter: this->mapper){
        delete iter.second;
        iter.second = nullptr;
        this->mapper.erase(iter.first);
    }
    for(auto iter: this->global){
        delete iter.second;
        iter.second = nullptr;
        this->mapper.erase(iter.first);
    }
}

void Mapper::read_mapper(const std::string& path){
    boost::property_tree::ptree pt;
    boost::property_tree::read_ini(path, pt);
    try{
        boost::property_tree::ptree global = pt.get_child("global");
        try{
            this->global["default_dynamic_library"] = new std::string{global.get<std::string>("default_dynamic_library")};
        }
        catch(...){}
        try{
            this->global["default_location"] = new std::string{global.get<std::string>("default_location")};
        }
        catch(...){}
        try{
            this->global["403_page"] = new std::string{global.get<std::string>("403_page")};
        }
        catch(...){}
        try{
            this->global["404_page"] = new std::string{global.get<std::string>("404_page")};
        }
        catch(...){}
        try{
            this->use_mysql = global.get<std::string>("use_mysql") == "1" ? true : false;
        }
        catch(...){}
    }
    catch (...){}
    try{
        for(int i = 0;i < 128;i++){
            std::string mapper_path = "mapper" + std::to_string(i);
            boost::property_tree::ptree mapper = pt.get_child(mapper_path);
            MapperEntity* mapper_entity = new MapperEntity{};
            std::string method, path, location, dynamic_library, function_name;
            try{
                method = mapper.get<std::string>("method");
            }
            catch(...){}
            try{
                path = mapper.get<std::string>("path");
            }
            catch(...){}
            try{
                location = mapper.get<std::string>("location");
            }
            catch(...){}
            try{
                dynamic_library = mapper.get<std::string>("dynamic_library");
            }
            catch(...){}
            try{
                function_name = mapper.get<std::string>("function_name");
            }
            catch(...){}
            Utils::set_method(method.c_str(), &mapper_entity->method);
            mapper_entity->function_name = function_name;
            if(location != "")
                mapper_entity->location = location;
            else
                mapper_entity->location = this->global["default_location"]->c_str();
            if(dynamic_library != "")
                mapper_entity->dynamic_library = dynamic_library;
            else
                mapper_entity->dynamic_library = this->global["default_dynamic_library"]->c_str();
            this->mapper[path] = mapper_entity;
        }
    }
    catch (...){}
    try{
        boost::property_tree::ptree mysql = pt.get_child("mysql");

    }
    catch (...){}
}

MapperEntity* Mapper::get_mapper(std::string name){
    return this->mapper[name];
}

Mapper::Mapper() {
    char* path = new char[256];
    strcpy(path, Utils::utils->get_resources()->get_config("RootDoc"));
    strcat(path, "/Security/conf/mapper.cnf");
    this->read_mapper(path);
    delete[] path;
}

std::string *Mapper::get_global(std::string name) {
    return this->global[name];
}
