#include <iostream>
#include "headers/application.h"
#include "headers/Utils.h"

int main(){
    application* app =  new application{};

    delete app;
    return 0;
}
