cmake_minimum_required(VERSION 3.10)
project(keesto)

set(CMAKE_CXX_STANDARD 14)

add_executable(keesto main.cpp application.cpp application.h Utils.h Resources.cpp Resources.h Utils.cpp Define.h Socket.cpp Socket.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(keesto Threads::Threads)
