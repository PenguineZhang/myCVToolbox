cmake_minimum_required(VERSION 3.1.0)
project(corner_detector)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

include_directories( 
    include
    ${OpenCV_INCLUDE_DIRS} 
)

file(GLOB FILES src/*.cpp include/*.hpp)

add_executable(corner_detector ${FILES})

target_link_libraries(corner_detector ${OpenCV_LIBS})
