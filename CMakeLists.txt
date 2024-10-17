# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(dedup VERSION 1.0)

set(
    SOURCES 
    src/dedup.c 
    src/md5.c 
    src/hash.c 
    src/rabinhash32.c 
    src/checksum.c 
    src/libz.c 
    src/listdb.c 
    src/bloom.c 
    src/hashdb.c 
    src/bighashtable.c
)

# 查找源文件
# file(GLOB SOURCES "src/*.c")

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 指定输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 包含头文件目录
# include_directories(include)

find_package(ZLIB REQUIRED)

# 链接库 (如果有外部库)
target_link_libraries(${PROJECT_NAME} PRIVATE ZLIB::ZLIB)

# 编译选项 (如需添加)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wimplicit-fallthrough=3 -std=gnu99)

# 定义预处理宏 (如果需要)
add_definitions(-DDEBUG)

# 测试 (如果需要)
# enable_testing()
# add_test(NAME MyTest COMMAND ${PROJECT_NAME})