cmake_minimum_required(VERSION 3.22)
project(Proyecto-ventas-SUD)  # <--- ESTE nombre debe coincidir con el de tu proyecto

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)

add_executable(Proyecto-ventas-SUD  # <--- ESTE también
        main.cpp
        src/Operaciones.cpp
)
