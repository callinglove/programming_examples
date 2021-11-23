cmake_minimum_required(VERSION 2.8)

project(demo)

# install
IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr/local/bin" CACHE PATH "set install path is /usr/local/bin" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

include(Config.cmake)

# 设置PKG_CONFIG_PATH与CMAKE_MODULE_PATH
# set(ENV{PKG_CONFIG_PATH} /opt/jrtplib3/lib/pkgconfig:/opt/ffmpeg-4.3.2/lib/pkgconfig)
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# ffmpeg
pkg_check_modules(FFMPEG REQUIRED libavformat libavcodec libavutil libswscale libswresample)
link_directories(${FFMPEG_LIBRARY_DIRS})
include_directories(${FFMPEG_INCLUDE_DIRS})

pkg_check_modules(SDL2 REQUIRED sdl2)
link_directories(${SDL2_LIBRARY_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})

message(STATUS "${FFMPEG_LIBRARY_DIRS}")
message(STATUS "${FFMPEG_INCLUDE_DIRS}")

string(TIMESTAMP VERSION "%Y-%m-%d %H:%M")
add_definitions(-DVERSION="${VERSION}")

add_executable(pix_fmt_dsc pix_fmt_dsc.c)
target_link_libraries(pix_fmt_dsc ${FFMPEG_LIBRARIES})

add_executable(fill_frame fill_frame.c)
target_link_libraries(fill_frame ${FFMPEG_LIBRARIES})

add_executable(display_yuv display_yuv.c)
target_link_libraries(display_yuv ${FFMPEG_LIBRARIES} ${SDL2_LIBRARIES})

INSTALL(TARGETS pix_fmt_dsc fill_frame
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# add_executable(test_audio_demo test_audio_demo.cpp ${src_files})
# target_compile_definitions(test_audio_demo PUBLIC -DTEST_DEMO)
