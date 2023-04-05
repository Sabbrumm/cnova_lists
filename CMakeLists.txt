cmake_minimum_required(VERSION 3.24)
project(list_lab)

set(CMAKE_CXX_STANDARD 17)


add_library(list STATIC list/list.cpp)
add_library(brum_cuts STATIC brum_cuts/brum_cuts.cpp)

add_executable(list_lab main.cpp)
target_link_libraries(list_lab PRIVATE list)
target_link_libraries(list_lab PRIVATE brum_cuts)