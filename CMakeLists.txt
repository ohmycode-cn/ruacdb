# Warning: The current compilation and source code are compatible with Windows 11/Linux 64 bit platforms. 
# If you need to adapt to other platforms, please configure it yourself (if you need to change the source 
# - code, we will not accept modified source code, even if pushed, it will be rejected)
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

if (WIN32)
    set(Qt6_ROOT "D:/AppProgram/CppQt/Qt6/6.11.1/msvc2022_64")
    set(CMAKE_PREFIX_PATH "${Qt6_ROOT}" CACHE PATH "Qt6 install root")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/cxx/*.cpp src/cxx/*.c)

if (NOT WIN32)
    add_compile_options(-Wall -Wextra -Wpedantic)
# else()
    # add_compile_options(-Wall -Wextra) # Use clang-cl.exe: ignore options parameter -Wpedantic. We are recommened disabled else() branch
endif()

# add_compile_options(-Werror) # Only specific system versions will enable strict mode
add_executable(${PROJECT_NAME} ${SOURCES} src/cxx/src/main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE src/cxx/include)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
