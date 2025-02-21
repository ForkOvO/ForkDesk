cmake_minimum_required(VERSION 3.16) # CMake最小版本要求
project(src) # 项目名称
aux_source_directory(./ SRC) # 添加源文件
add_library(${PROJECT_NAME} ${SRC}) # 创建库文件
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets) # 链接库