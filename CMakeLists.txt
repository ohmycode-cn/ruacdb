cmake_minimum_required(VERSION 4.3.1)
project(ruacdb LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/out)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON) 

if (NOT WIN32)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
endif()
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/cxx/*.cpp src/cxx/*.c)

add_compile_options(-Wall -Wextra -Wpedantic)
# add_compile_options(-Werror)
add_executable(${PROJECT_NAME} ${SOURCES} src/cxx/src/main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE src/cxx/include)
