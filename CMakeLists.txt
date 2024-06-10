cmake_minimum_required(VERSION 3.12)
project(gca)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")

# Include directories
include_directories(
    ${SRC_DIR}
    ${TEST_DIR}
    ${CMAKE_SOURCE_DIR}/bison
)

# Add executable
add_executable(gca ${SRC_FILES} ${SRC_DIR}/main/main.cpp)

# Set compiler flags for gca target
target_compile_options(gca PRIVATE -Wall -Wextra -g)
