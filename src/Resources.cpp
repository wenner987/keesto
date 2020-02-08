//
// Created by Wenner on 2020/1/14.
//

#include <fstream>
#include <cstring>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "headers/Resources.h"
#include "headers/Define.h"

Resources::Resources(){
    this->read_conf(CONF_LOCATION);
}

Resources::~Resources(){
}

void Resources::read_conf(std::string path){
    boost::property_tree::ptree pt;
    boost::property_tree::read_ini(path, pt);
    std::string root_doc, port;
    try{
        root_doc = pt.get<std::string>("RootDoc");
    }
    catch(...){}
    try{
        port = pt.get<std::string>("Port");
    }
    catch(...){}
    this->global_cnf["RootDoc"] = root_doc;
    this->global_cnf["Port"] = port;
}

const char* Resources::get_config(const char* name){
    return this->global_cnf[name].c_str();
}
