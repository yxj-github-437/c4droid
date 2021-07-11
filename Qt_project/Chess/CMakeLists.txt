cmake_minimum_required(VERSION 3.18.6)
project(build VERSION 0.1.0)

include(CTest)
enable_testing()

 #设置工程包含当前目录，非必须
 set(CMAKE_INCLUDE_CURRENT_DIR ON)
 
 #打开全局moc,设置自动生成moc文件，一定要设置
 set(CMAKE_AUTOMOC ON)
 #打开全局uic，非必须
 set(CMAKE_AUTOUIC ON)

 #查找需要的Qt库文件，最好每一个库都要写，Qt也会根据依赖关系自动添加
 find_package(Qt5Widgets)

 #查找当前文件夹中的所有源代码文件，也可以通过Set命令将所有文件设置为一个变量
 FILE(GLOB SRC_FILES "./*.cpp")
 #查找设置当前文件夹中所有的头文件
 FILE(GLOB HEAD_FILES "./*.h")
 #查找设置当前文件夹中所有的ui文件
 FILE(GLOB UI_FILES "./*.ui")

 #通过Ui文件生成对应的头文件，一定要添加
 qt5_wrap_ui(WRAP_FILES ${UI_FILES})

 #将ui文件和生成文件整理在一个文件夹中，非必须
 source_group("Ui" FILES ${UI_FILES} ${WRAP_FILES} )

 #创建工程文件
 add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES} ${HEAD_FILES} ${WRAP_FILES})
 
 #添加Qt5依赖项
 target_link_libraries(${PROJECT_NAME} Qt5::Widgets)