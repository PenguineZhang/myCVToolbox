cmake_minimum_required(VERSION 3.1.0)
project(myCVtools)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

add_subdirectory(components)

add_executable(main main.cpp)

target_link_libraries(main corner_detector utils)
