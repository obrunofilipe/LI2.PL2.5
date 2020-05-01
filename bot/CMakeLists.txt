cmake_minimum_required(VERSION 3.16)
project(bot)

set(CMAKE_C_STANDARD 99)

add_executable(bot main.c camada_de_dados.c camada_de_dados.h camada_de_interface.c camada_de_interface.h logica_do_programa.c logica_do_programa.h listas.c listas.h)