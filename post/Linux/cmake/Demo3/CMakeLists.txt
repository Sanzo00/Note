# Cmake最低版本号
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
