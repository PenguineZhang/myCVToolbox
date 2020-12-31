add_library(utils utils.cpp utils.hpp)

find_package(OpenCV REQUIRED)
target_link_libraries(utils ${OpenCV_LIBS})