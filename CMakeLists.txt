cmake_minimum_required(VERSION 3.15)
project(50Questoes)

set(CMAKE_CXX_STANDARD 14)

add_executable(LI2 main.c camada_de_dados.c camada_de_dados.h camada_de_interface.c camada_de_interface.h logica_do_programa.c logica_do_programa.h listas.c listas.h )