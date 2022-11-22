cmake_minimum_required(VERSION 3.23)
project(avl C)

set(CMAKE_C_STANDARD 11)

add_executable(avl
        main.c
        avl.c
        avl.h
        )
