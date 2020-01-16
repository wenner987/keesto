//
// Created by Wenner on 2020/1/14.
//

#ifndef KEESTO_UTILS_H
#define KEESTO_UTILS_H

#include <boost/shared_ptr.hpp>
#include "Resources.h"


class Utils {
private:
    std::shared_ptr<Resources> resources;
public:
    Utils();

    static std::shared_ptr<Utils> utils;

    std::shared_ptr<Resources> getResources(){
        return this->resources;
    }
};


#endif //KEESTO_UTILS_H
