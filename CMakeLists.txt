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

# Include local configuration (create local.cmake for your environment)
include(local.cmake)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/cxx/*.cpp src/cxx/*.c)

# Unit test control: -DUNIT_TEST=ON (default) or -DUNIT_TEST=OFF
option(UNIT_TEST "Enable unit tests" ON)

if (NOT UNIT_TEST)
    # Production build: exclude test sources and test headers from compilation
    list(FILTER SOURCES EXCLUDE REGEX ".*/google_test/.*")
    list(FILTER SOURCES EXCLUDE REGEX ".*/test/.*")
else()
    # Google Test (vendored) — built as a library target via its own CMakeLists.txt.
    # The glob above only matches *.cpp/*.c so vendored *.cc files are NOT double-compiled.
    set(gtest_dir ${CMAKE_SOURCE_DIR}/src/cxx/include/google_test/api/googletest)
    add_subdirectory(${gtest_dir} ${CMAKE_BINARY_DIR}/googletest EXCLUDE_FROM_ALL)
endif()

if (NOT WIN32)
    add_compile_options(-Wall -Wextra -Wpedantic)
# else()
    # add_compile_options(-Wall -Wextra) # Use clang-cl.exe: ignore options parameter -Wpedantic. We are recommened disabled else() branch
endif()

# add_compile_options(-Werror) # Only specific system versions will enable strict mode
add_executable(${PROJECT_NAME} ${SOURCES} src/cxx/src/main.cpp)

if (WIN32)
    # Prevent Windows SDK (minwindef.h) from defining min/max macros,
    # which conflict with std::min / std::max in <algorithm>.
    # Without this, calls like std::max(a, b) get text-substituted into
    # invalid syntax, causing "expected unqualified-id" errors.
    target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")

if (UNIT_TEST)
    target_compile_definitions(${PROJECT_NAME} PRIVATE UNIT_TEST)
    target_include_directories(${PROJECT_NAME} PRIVATE
        src/cxx/include
        ${gtest_dir}/googletest/include    # gtest/gtest.h
        ${gtest_dir}/googlemock/include    # gmock/gmock.h
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets gtest)
else()
    target_include_directories(${PROJECT_NAME} PRIVATE src/cxx/include)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
endif()
