cmake_minimum_required(VERSION 3.10)
project(SOKOBAN)

set(CMAKE_CXX_STANDARD 17)

#set(COMMON_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system")
#add_definitions(${COMMON_FLAGS})

SET(GCC_COVERAGE_COMPILE_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system")
SET(GCC_COVERAGE_LINK_FLAGS    "-lsfml-graphics -lsfml-window -lsfml-system")
set (CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

#target_compile_options(source.cpp PRIVATE -lsfml-graphics -lsfml-window -lsfml-system)

set_property(TARGET sokoban APPEND_STRING PROPERTY LINK_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system")

add_executable(sokoban source.cpp)
