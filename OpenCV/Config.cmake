
### compiler
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    if (UNIX)
        set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-rdynamic")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++
endif()

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_definitions(-DDEBUG)
endif()

if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    add_definitions(-DRELEASE)
endif()

### include/link dir
include_directories(${CMAKE_SOURCE_DIR}/lib/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_BINARY_DIR}/target)

### output
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target)

# install
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

# RPATH
set(CMAKE_SKIP_BUILD_RPATH FALSE)                       # 编译时加上RPATH
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)               # 编译时是否使用安装的RPATH
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")  # 安装RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)            # 安装的执行文件不加上RPATH

### macro
macro(dennis_aux_dirs RET)
    foreach(_dir ${ARGN})
        aux_source_directory(${_dir} ${RET})
    endforeach()
endmacro()

macro(dennis_aux_depend TARGETNAME)
    add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/.${TARGETNAME}__auxdepend
        COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_SOURCE_DIR}/CMakeLists.txt
        COMMAND make depend
        COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_BINARY_DIR}/.${TARGETNAME}__auxdepend
        DEPENDS ${ARGN}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "update Makefile for ${PROJECT_NAME}"
        VERBATIM)
    add_custom_target(${TARGETNAME}__auxdepend ALL DEPENDS ${PROJECT_BINARY_DIR}/.${TARGETNAME}__auxdepend)
    add_dependencies(${TARGETNAME} ${TARGETNAME}__auxdepend)
endmacro()