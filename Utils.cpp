//
// Created by Wenner on 2020/1/14.
//

#include "Utils.h"

std::shared_ptr<Utils> Utils::utils = std::make_shared<Utils>();

Utils::Utils(){
    this->resources = std::make_shared<Resources>();
}
