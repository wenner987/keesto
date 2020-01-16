#include <iostream>
#include "application.h"

int main(){
    application* app =  new application{};

    delete app;
    return 0;
}
