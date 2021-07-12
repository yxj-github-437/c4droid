cmake_minimum_required(VERSION 3.16)
project(test)
aux_source_directory(. SRC_LIST)
#生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_LIST})
#链接对应的函数库
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image)