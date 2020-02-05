//
// Created by Wenner on 2020/2/4.
//

#ifndef KEESTO_MYSQLCONFIG_H
#define KEESTO_MYSQLCONFIG_H

#include <string>

class MysqlConfig{
    std::string path;
    std::string username;
    std::string password;
    int max_connection;
    int min_connection;
public:
    const std::string &get_path() const {return path;}

    void set_path(const std::string &path) {MysqlConfig::path = path;}

    const std::string &get_username() const {return username;}

    void set_username(const std::string &username) {MysqlConfig::username = username;}

    const std::string &get_passwrd() const {return password;}

    void set_password(const std::string &password) {MysqlConfig::password = password;}

    int get_max_connection() const {return max_connection;}

    void set_max_connection(int maxConnection) {max_connection = maxConnection;}

    int get_min_connection() const {return min_connection;}

    void set_min_connection(int minConnection) {min_connection = minConnection;}

};

#endif //KEESTO_MYSQLCONFIG_H
