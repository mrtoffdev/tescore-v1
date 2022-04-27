cmake_minimum_required(VERSION 3.22)
project(Tescore C)

set(CMAKE_C_STANDARD 99)

add_executable(
        Tescore main.c

        include/io/io.h
        include/io/encrypt.c
        include/io/crud.c
        include/io/decrypt.c
        include/io/lib/aes.c
        include/io/lib/aes.h

        include/model/index.h
        include/model/sheet.h
        include/model/subsheet.h include/model/datamodel.h)
