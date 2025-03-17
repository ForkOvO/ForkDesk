cmake_minimum_required(VERSION 3.16) # CMake最小版本要求
project(public) # 项目名称

aux_source_directory(./ PUBLIC_SRC) # 添加源文件
add_library(${PROJECT_NAME} ${PUBLIC_SRC}) # 创建库文件

target_link_libraries(${PROJECT_NAME} PRIVATE
    # QT6
    Qt6::Widgets
) # 链接库