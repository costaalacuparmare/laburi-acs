cmake_minimum_required(VERSION 3.24)
project(Tema2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Tema2
        auxiliary.c
        main.c
        quadtree.h
        stats.c
        compress.c
        decompress.c)
