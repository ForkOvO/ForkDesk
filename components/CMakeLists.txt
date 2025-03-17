cmake_minimum_required(VERSION 3.16) # CMake最小版本要求
project(components) # 项目名称

include_directories(../public) # 添加子目录

aux_source_directory(./ SOFTWARE_SRC) # 添加源文件
add_library(${PROJECT_NAME} ${SOFTWARE_SRC}) # 创建库文件

target_link_libraries(${PROJECT_NAME} PRIVATE
    # QT6
    Qt6::Widgets
    # 自定义
    public
) # 链接库