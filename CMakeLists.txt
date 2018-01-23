cmake_minimum_required(VERSION 3.9)
project(AVM)

set(CMAKE_CXX_STANDARD 17)

add_executable(AVM
        src/CPU/cpu.h
        src/Memory/memory.h)
