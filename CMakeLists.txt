cmake_minimum_required(VERSION 3.19) # CMake最低版本
get_filename_component(projectName ${CMAKE_CURRENT_SOURCE_DIR} NAME) # 获取目录名称
string(REPLACE " " "_" projectName ${projectName}) # 把空格替换成下划线（_）
project(${projectName} C) # C的项目名称,如果是C++则把C更改成C++
set(CMAKE_C_STANDARD 11) # C语言版本

set(RedisDir redis/) # 设置执行文件的目录,用于切换执行目录
# set(RedisDir test)
# set(RedisDir practice-generic)
# set(RedisDir practice-extern)
# set(RedisDir ) # 切换成跟目录

set(RedisDir ${RedisDir}/)
set(srcList ${projectName}) # 需要导入的文件名变量，这里把项目名称写到变量里
file(GLOB filePathList "${CMAKE_CURRENT_SOURCE_DIR}/${RedisDir}*.c") # 获取目录下所有文件
foreach(filePath ${filePathList}) # 循环文件名
    get_filename_component(fileName ${filePath} NAME) # 获取文件名，这里${file}是绝对路径文件
    set(srcList ${srcList} ${RedisDir}${fileName}) # 文件名称
endforeach()

# message(${srcList} )
add_executable(${srcList}) # 添加C文件，用来生成可执行文件