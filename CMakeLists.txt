cmake_minimum_required(VERSION 3.12)
project(gca)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

set(SRC_FILES
  ${SRC_DIR}/cellular_automata/cellular_automata.cpp
  ${SRC_DIR}/graphics/sfml_front_end.cpp
  ${SRC_DIR}/rules/cartesian_r_one.cpp
)

# Include directories
include_directories(
    ${SRC_DIR}
)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add executable
add_executable(gca ${SRC_FILES} ${SRC_DIR}/main/main.cpp)

target_link_libraries(gca sfml-graphics sfml-window sfml-system)

# Set compiler flags for gca target
target_compile_options(gca PRIVATE -Wall -Wextra -g)
