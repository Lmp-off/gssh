cmake_minimum_required(VERSION 3.20)
project(gssh CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(gssh
    src/main.cpp
    src/graphics.cpp
    src/input.cpp
    # src/ssh.cpp
    src/terminal.cpp
)

target_include_directories(gssh PRIVATE include)
target_compile_options(gssh PRIVATE -Wall -Wextra -Wpedantic)