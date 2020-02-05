//
// Created by Wenner on 2020/1/14.
//

#include "headers/Utils.h"

#include "headers/application.h"
#include "headers/Socket.h"

#include <iostream>

application::application(){
    signal(SIGSEGV, Utils::single_handler);
    server_socket socket(1234);
}
