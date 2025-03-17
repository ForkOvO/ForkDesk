cmake_minimum_required(VERSION 3.16) # CMake最小版本要求
project(src) # 项目名称

# 添加子目录
include_directories(../components)
include_directories(../public)

aux_source_directory(./ SRC) # 添加源文件
add_library(${PROJECT_NAME} ${SRC}) # 创建库文件

target_link_libraries(${PROJECT_NAME} PRIVATE
    # QT6
    Qt6::Widgets
    # 自定义
    components
    public
) # 链接库
