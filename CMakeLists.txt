cmake_minimum_required(VERSION 3.10)
project(SOKOBAN)

set(CMAKE_CXX_STANDARD 17)

file( GLOB SRC "source/*.cpp")

add_executable(sokoban source.cpp ${SRC})
target_link_libraries(sokoban PRIVATE -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio stdc++fs -pthread)
target_include_directories(sokoban PUBLIC include)


add_executable(sokoban-multiplayer multiplayer.cpp ${SRC})
target_link_libraries(sokoban-multiplayer PRIVATE -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio stdc++fs -pthread)
target_include_directories(sokoban-multiplayer PUBLIC include)
