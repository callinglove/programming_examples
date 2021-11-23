# CMAKE_INSTALL_BINDIR等变量
include(GNUInstallDirs)

# 检查c++编译器标志，设置c++11支持变量
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

# 使用变量设置编译标志
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    add_definitions(-DNDEBUG)
endif()

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--as-needed ${CMAKE_SHARED_LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--as-needed ${CMAKE_MODULE_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed ${CMAKE_EXE_LINKER_FLAGS}")

### include/link dir
include_directories(${CMAKE_SOURCE_DIR}/lib/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_BINARY_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR})

### output
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)   # cmake生成compile_commands.json，包含所有编译单元所执行的指令

# RPATH
set(CMAKE_SKIP_BUILD_RPATH TRUE)                       # 编译时是否忽略编译RPATH
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)               # 编译时是否使用安装的RPATH
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")  # 安装RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)            # 安装的执行文件不加上RPATH

# pkg-config
# /usr/share/cmake/Modules/FindPkgConfig.cmake
# 查找pkg-config程序
# PKG_CONFIG_FOUND          ... if pkg-config executable was found
# PKG_CONFIG_EXECUTABLE     ... pathname of the pkg-config program
# PKG_CONFIG_VERSION_STRING ... the version of the pkg-config program found
#                               (since CMake 2.8.8)
find_package(PkgConfig)

### macro
macro(aux_source_directories RET)
    foreach(_dir ${ARGN})
        aux_source_directory(${_dir} ${RET})
    endforeach()
    include_directories(${ARGN})
    link_directories(${ARGN})
endmacro()

