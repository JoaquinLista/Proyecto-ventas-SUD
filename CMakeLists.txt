cmake_minimum_required(VERSION 3.22)
project(Proyecto-ventas-SUD)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)

add_executable(Proyecto-ventas-SUD
        main.cpp
        src/Operaciones.cpp
        includes/ArbolVentas.h)
