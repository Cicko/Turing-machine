cmake_minimum_required(VERSION 3.6)
project(turing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp
    Node.cpp
    Node.hpp
    State.cpp
    State.hpp
    Tape.cpp
    Tape.hpp
    Turing.cpp
    Turing.hpp)

add_executable(turing ${SOURCE_FILES})