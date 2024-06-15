cmake_minimum_required(VERSION 3.28)
project(Atividade___Comparacao_AVL_e_Rubro_Negra C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Atividade___Comparacao_AVL_e_Rubro_Negra
        avl.c
        avl.h
        main.c
        rubro_negra.c
        rubro_negra.h
        ops_avl.c
        ops_avl.h
        ops_rn.c
        ops_rn.h)
