## 同一个目录, 多个源文件

```bash
./Demo1
	|
	+--- include/
		|
		+--- add.h
	+--- src/
		|
		+--- add.c
		+--- main.c
```

```bash

# Cmake最低版本号
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo1)

# 指定头文件目录
include_directories(include)

# 将src下的源文件保存到DIR_SRCS变量中
aux_source_directory(src DIR_SRCS)

# 指定生成目标
add_executable(Demo1 ${DIR_SRCS})

```

## 多个目录, 多个源文件

```bash
./Demo2
	|
	+--- src
	|	|
	|	+--- add.h
	|	|
	|	+--- add.c
	|
	+--- test
		|
		+--- main.c
```

需要在src和根目录编写CMakeLists.txt, 将src中的文件编译为静态库文件由main函数调用

- 根目录下CMakelists.txt
    ```bash

    # Cmake最低版本号
    cmake_minimum_required (VERSION 2.8)

    # 项目信息
    project (Demo2)

    # 将test下的源文件保存到DIR_SRCS变量中
    aux_source_directory(test DIR_SRCS)

    # 指定头文件目录
    include_directories(src)

    # 添加src子目录
    add_subdirectory(src)

    # 指定生成目标
    add_executable(Demo2 ${DIR_SRCS})

    # 添加链接库
    target_link_libraries(Demo2 add)

    ```

- 子目录(src)下CMakelists.txt

    ```bash

    make最低版本号
    cmake_minimum_required (VERSION 2.8)

    # 将当前目录下的源文件保存到DIR_SRCS变量中
    aux_source_directory(. DIR_LIB_SRCS)

    # 生成链接库
    add_library(add ${DIR_LIB_SRCS})

    ```

## 自定义编译选项
将pow库设置为一个可选的库, 如果选项为ON, 就是使用自定义库, 否则使用标准库

- CmakeLists.txt

    ```bash

    make最低版本号
    cmake_minimum_required (VERSION 2.8)

    # 项目信息
    project (Demo3)

    # 加入配置头文件, 处理CMake对源码的设置
    configure_file (
        "${PROJECT_SOURCE_DIR}/config.h.in"
            "${PROJECT_BINARY_DIR}/config.h"
    )

    # 是否使用自己的pow库
    option (USE_MYPOW
            "Use provided pow implementation" ON
    )

    # 是否加入pow库
    if (USE_MYPOW) 
        include_directories ("${PROJECT_SOURCE_DIR}/src" .)
        add_subdirectory (src)
        set (EXTRA_LIBS ${EXTRA_LIBS} pow)
    endif (USE_MYPOW)

    # 将test下的源文件保存到DIR_SRCS变量中
    aux_source_directory(test DIR_SRCS)

    # 指定生成目标
    add_executable(Demo3 ${DIR_SRCS})

    # 添加链接库
    target_link_libraries(Demo3 pow)
    ```

- 修改main.c

    ```bash
    #include <stdio.h>
    #include <stdlib.h>
    #include "config.h"

    #ifdef USE_MYPOW
        #include "pow.h"
    #else
        #include <math.h>
    #endif

    int main(int argc , char *argv[]) {
        if (argc < 3) printf("argv error!");
        double x = atof(argv[1]);
        int y = atoi(argv[2]);
    #ifdef USE_MYPOW
        printf("My pow:\n");
        double res = pow(x, y);
    #else
        printf("standard pow:\n");
        double res = pow(x, y);
    #endif

        printf("%g ^ %d = %g\n", x, y, res);
        return 0;
    }
    ```

- 编写config.h.in
main.c有config.h, CMake可以根据config.h.in自动生成config.h

    ```bash
        #cmakedefine USE_MYPOW
    ```

