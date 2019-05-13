
## OpenMP简介

OpenMP 是 Open MultiProcessing 的缩写。OpenMP 并不是一个简单的函数库，而是一个诸多编译器支持的框架，或者说是协议吧，总之，不需要任何配置，你就可以在 Visual Studio 或者 gcc 中使用它了。

项目添加OpenMP支持:

- 【VS操作】菜单栏->Project->Properties，弹出菜单里，点击 Configuration Properties->C/C++->Language->OpenMP Support，在下拉菜单里选择Yes。
- 【gcc操作】 在编译时添加-fopenmp参数
- 【CMake】
```
cmake_minimum_required(VERSION 2.8)
project(openmp_test)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_BUILD_TYPE Debug)

FIND_PACKAGE( OpenMP REQUIRED)

if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(openmp_test openmp_test.cpp)
target_link_libraries(openmp_test ${OpenMP_LIBS})
```

## 指令使用

OpenMP 对可以多线程化的循环有如下五个要求：

- 循环的变量变量（就是i）必须是有符号整形，其他的都不行。
- 循环的比较条件必须是< <= > >=中的一种
- 循环的增量部分必须是增减一个不变的值（即每次循环是不变的）。
- 如果比较符号是< <=，那每次循环i应该增加，反之应该减小
- 循环必须是没有奇奇怪怪的东西，不能从内部循环跳到外部循环，goto和break只能在循环内部跳转，异常必须在循环内部被捕获。

### 管理公有和私有数据

基本上每个循环都会读写数据，确定那个数据时线程之间共有的，那些数据时线程私有的就是程序员的责任了。
当数据被设置为公有的时候，所有的线程访问的都是相同的内存地址，当数据被设为私有的时候，每个线程都有
自己的一份拷贝。默认情况下，除了循环变量以外，所有数据都被设定为公有的。可以通过以下两种方法把变量
设置为私有的：

- 在循环内部声明变量，注意不要是static的
- 通过OpenMP指令声明私有变量

```
// 下面这个例子是错误的
int temp; // 在循环之外声明
#pragma omp parallel for
for (int i = 0; i < 100; i++) {
    temp = array[i];
    array[i] = doSomething(temp);
}
```

可以通过以下两种方法改正

```
// 1. 在循环内部声明变量
#pragma omp parallel for
for (int i = 0; i < 100; i++) {
    int temp = array[i];
    array[i] = doSomething(temp);
}
```
```
// 2. 通过OpenMP指令说明私有变量
int temp;
#pragma omp parallel for private(temp)
for (int i = 0; i < 100; i++) {
    temp = array[i];
    array[i] = doSomething(temp);
}
```


参考:

- [OpenMP 入门教程](https://www.cnblogs.com/ospider/p/5265975.html)

扩展阅读:

- [GCC 4.4.7 GNU OpenMP Manual](https://gcc.gnu.org/onlinedocs/gcc-4.4.7/libgomp/)
- [parallel programming tutorials](https://hpc.llnl.gov/training/tutorials)