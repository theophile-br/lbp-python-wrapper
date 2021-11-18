cmake_minimum_required(VERSION 3.00)
project(clbp)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(clbp clbp.cpp)
target_link_libraries(clbp ${OpenCV_LIBS})
file(COPY pylbp.py DESTINATION ${CMAKE_BINARY_DIR})

