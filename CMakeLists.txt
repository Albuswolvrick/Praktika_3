cmake_minimum_required(VERSION 3.10)
project(praktikum3 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(praktikum3
        main.c
        rechner.h
        addition.c
        subtraktion.c
        multiplikation.c
        division.c
        fakultaet.c
        fakultaet_rekursiv.c
        fibonacci_rekursiv.c
        fibonacci_iterativ.c)
