cmake_minimum_required(VERSION 3.29)
project(fruit_project)

set(CMAKE_CXX_STANDARD 11)

add_executable(fruit_project src/main.cc
        src/fruit.hh
        src/fruit.cc
        src/fruit_farm.cc
        src/fruit_farm.hh
        src/constants.hh
        src/dynamic_array.hh
        src/utility.hh
        src/system_ui.cc
        src/system_ui.hh
        src/farmer.cc
        src/farmer.hh
        src/utility.cc
        src/request_generator.cc
        src/request_generator.hh
)
