cmake_minimum_required(VERSION 4.3)
project(termlite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/out)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)

add_compile_options(-Wall -Wextra -Wpedantic)
# add_compile_options(-Werror)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
add_executable(termlite termlite.cpp)
