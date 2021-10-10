cmake_minimum_required(VERSION 3.20)
project(database)

set(CMAKE_CXX_STANDARD 17)

add_executable(database main.cpp database.cpp database.h)
