cmake_minimum_required(VERSION 2.8)

project(ffmpeg_tutorial)

include(Config.cmake)

# set(CMAKE_CXX_STANDARD 98)
set(CMAKE_BUILD_TYPE Debug)

pkg_check_modules(FFMPEG REQUIRED
    libavdevice
    libavformat
    libavfilter
    libavcodec
    libswresample
    libswscale
    libavutil
)
include_directories(${FFMPEG_INCLUDE_DIRS})
link_directories(${FFMPEG_LIBRARY_DIRS})

add_executable(transcode_aac transcode_aac.c)
target_link_libraries(transcode_aac ${FFMPEG_LIBRARIES})

INSTALL(TARGETS test
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION libstatic)
