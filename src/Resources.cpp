//
// Created by Wenner on 2020/1/14.
//

#include <fstream>
#include <cstring>
#include <iostream>

#include "headers/Resources.h"
#include "headers/Socket.h"

Resources::Resources(){
    this->read_conf(CONF_LOCATION);
}

Resources::~Resources(){
}

void Resources::read_conf(std::string path){
    std::ifstream ifs{path, std::ios::binary};

    std::string cnf_line;
    char* front = new char[32];
    char* end = new char[32];
    while(getline(ifs, cnf_line)){
        if(cnf_line == "") continue;
        int status = 0; // record front or end in a line
        int i;
        int pos_in_sub = 0;
        for(i = 0;cnf_line[i] != '#' && cnf_line[i] != '\0';++i){
            if(cnf_line[i] == '='){
                status = 1;
                front[pos_in_sub] = 0;
                pos_in_sub = 0;
            }
            else if(cnf_line[i] == ' '){
                continue;
            }
            else{
                if(status == 0) front[pos_in_sub++] = cnf_line[i];
                else end[pos_in_sub++] = cnf_line[i];
            }
        }
        end[pos_in_sub] = 0;
        global_cnf[front] = end;
    }
}

const char* Resources::getConfig(const char* name){
    return this->global_cnf[name].c_str();
}
