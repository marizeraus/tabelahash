cmake_minimum_required(VERSION 3.10)
project(encadeamento-exterior-disco)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(encadeamento-exterior-disco
        cliente.c
        cliente.h
        compartimento_hash.c
        compartimento_hash.h
        encadeamento_exterior.c
        encadeamento_exterior.h
        lista_clientes.c
        lista_clientes.h
        lista_compartimentos.c
        lista_compartimentos.h
        Makefile
        test_encadeamento_exterior.c
        ufftest.h)
