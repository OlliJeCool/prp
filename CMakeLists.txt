cmake_minimum_required(VERSION 3.30)
project(prp C)

set(CMAKE_C_STANDARD 11)

include_directories(hw/hw08)

add_executable(prp
    hw/hw08/queue.c
    hw/hw08/queue.h
        hw/hw08/main.c)
