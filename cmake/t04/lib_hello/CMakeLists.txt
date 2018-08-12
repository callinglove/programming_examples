AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_LIBRARY(hello_shared SHARED ${SRC_LIST}) # lib的名字不能重复
ADD_LIBRARY(hello_static STATIC ${SRC_LIST})
SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")
SET_TARGET_PROPERTIES(hello_shared PROPERTIES OUTPUT_NAME "hello")

# 设置动态库的版本号
SET_TARGET_PROPERTIES(hello_shared PROPERTIES VERSION 1.2 SOVERSION 1)

# 如果发现后来生成的lib清除了同名的早先生成的lib，（只有一个静态库或动态库生成）
# 试下下面两个命令
# 较新版本的cmake不再需要下面两个命令就可以同时生成hello.so hello.a
#SET_TARGET_PROPERTIES(hello_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#SET_TARGET_PROPERTIES(hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

GET_TARGET_PROPERTY (OUTPUT_VALUE hello_static OUTPUT_NAME)
MESSAGE (STATUS "This is the hello_static OUTPUT_NAME: " ${OUTPUT_VALUE})

# 我们需要将libhello.a, libhello.so.x以及hello.h安装到系统目录，才能真正让其他人开发使用，
# 在本例中我们将hello的共享库安装到<prefix>/lib目录；
# 将hello.h安装<prefix>/include/hello目录。
# 静态库要使用ARCHIVE关键字
# 指定<prefix> cmake -DCMAKE_INSTALL_PREFIX=/usr/loal
INSTALL(TARGETS hello_shared hello_static 
	LIBRARY DESTINATION lib 
	ARCHIVE DESTINATION lib)
INSTALL(FILES hello.h DESTINATION include/hello)



