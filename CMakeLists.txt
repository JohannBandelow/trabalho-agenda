cmake_minimum_required(VERSION 3.26)
project(trabalho_agenda C)

set(CMAKE_C_STANDARD 11)

add_executable(trabalho_agenda main.c
        Data.c
        Evento.c
        Horario.c
        Lista.c)
