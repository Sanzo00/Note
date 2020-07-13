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
