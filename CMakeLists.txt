cmake_minimum_required(VERSION 3.1.0)
project(myCVtools)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

add_subdirectory(components)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC components)
target_link_directories(${PROJECT_NAME} PUBLIC components)
target_link_libraries(${PROJECT_NAME} corner_detector utils)
