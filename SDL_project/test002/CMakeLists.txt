cmake_minimum_required(VERSION 3.16)
project(test)
aux_source_directory(. SRC_LIST)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
#生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_LIST})
#链接对应的函数库
target_link_libraries(${PROJECT_NAME} SDL2)