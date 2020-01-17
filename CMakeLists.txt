cmake_minimum_required(VERSION 3.10)
project(keesto)

set(CMAKE_CXX_STANDARD 14)

add_executable(keesto
        src/main.cpp
        src/application.cpp
        src/headers/application.h
        src/headers/Utils.h
        src/Resources.cpp
        src/headers/Resources.h
        src/Utils.cpp
        src/headers/Define.h
        src/Socket.cpp
        src/headers/Socket.h
        src/WebServer.cpp
        src/HttpRequest.cpp
        src/headers/HttpRequest.h
        src/HttpResponse.cpp
        src/headers/HttpResponse.h
        src/HttpString.cpp
        src/headers/HttpString.h
        src/exception/exception.h
        src/exception/FileNotFoundException.h
        src/exception/IllegalAccessException.h
        )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(keesto Threads::Threads)
