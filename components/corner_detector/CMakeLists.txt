add_library(corner_detector CornerDetector.cpp CornerDetector.hpp)

find_package(OpenCV REQUIRED)
target_link_libraries(corner_detector ${OpenCV_LIBS})