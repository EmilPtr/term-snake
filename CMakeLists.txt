cmake_minimum_required(VERSION 4.0)
project(term_snake C)

set(CMAKE_C_STANDARD 23)

add_executable(term_snake
        main.c
        terminal.c
        snake.c)
