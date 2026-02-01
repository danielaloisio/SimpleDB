cmake_minimum_required(VERSION 3.31.6)
project(SimpleDB)

set(CMAKE_CXX_STANDARD 20)

add_executable(SimpleDB src/main.cpp
        src/Document.cpp
        src/Document.h
        src/Collection.cpp
        src/Collection.h
        src/DocumentDB.cpp
        src/DocumentDB.h)
