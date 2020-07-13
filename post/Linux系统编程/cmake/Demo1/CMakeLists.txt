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

