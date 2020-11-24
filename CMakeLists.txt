cmake_minimum_required(VERSION 3.1.0)
project(corner_detector)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(corner_detector CornerDetector.cpp)

target_link_libraries(corner_detector ${OpenCV_LIBS})