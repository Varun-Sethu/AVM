cmake_minimum_required(VERSION 3.9)
project(AVM)

set_target_properties(AVM PROPERTIES LINKER_LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(AVM
        src/Runtime/Memory/Memory.h)
