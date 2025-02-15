cmake_minimum_required(VERSION 3.20)
project(GarbageCollector C)

set(CMAKE_C_STANDARD 11)

add_executable(GarbageCollector main.c virtual_machine.h virtual_machine.c vm_object.h vm_object.c)
