# Cmake最低版本号
cmake_minimum_required (VERSION 2.8)

# 将当前目录下的源文件保存到DIR_SRCS变量中
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library(pow ${DIR_LIB_SRCS})
