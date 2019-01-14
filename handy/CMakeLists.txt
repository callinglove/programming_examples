cmake_minimum_required(VERSION 2.8)
project(handy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# set(CMAKE_PREFIX_PATH  /home/cuizhou/Downloads/opencv-3.3.0/build_cuda) #版本冲突可能导致PVADetector类detect函数中resize报错
# find_package(OpenCV 3.3.0 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Freetype)

include_directories(include)
IF(FREETYPE_FOUND)
  include_directories(${FREETYPE_INCLUDE_DIRS})
ENDIF()

file( COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${PROJECT_BINARY_DIR})
# configure_file(${PROJECT_SOURCE_DIR}/res/* ${PROJECT_BINARY_DIR}/res/* COPYONLY)

message(STATUS "CMAKE_SYSTEM_NAME : ${CMAKE_SYSTEM_NAME}")
message(STATUS "WIN32 : ${WIN32}")
message(STATUS "MINGW : ${MINGW}")
message(STATUS "MSVC  : ${MSVC}")
if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

add_subdirectory(src)
add_subdirectory(executable)