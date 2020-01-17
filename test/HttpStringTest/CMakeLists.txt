cmake_minimum_required(VERSION 3.10)
project(string_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(string_test test_main.cpp ../../src/headers/HttpString.h ../../src/HttpString.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(string_test Threads::Threads)
