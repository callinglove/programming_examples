cmake_minimum_required(VERSION 2.8)

project(OpenCV_tutorial)

include(Config.cmake)

# set(CMAKE_CXX_STANDARD 98)
# set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED core imgproc video highgui)

add_subdirectory(contours)
add_subdirectory(Histogram)
add_subdirectory(kmeans)
add_subdirectory(tools)
