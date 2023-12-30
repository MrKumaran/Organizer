cmake_minimum_required(VERSION 3.27)
project(Organizer C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Organizer
        Organizer.c
        Organizer.h)
