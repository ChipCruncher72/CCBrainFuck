cmake_minimum_required(VERSION "3.28.3")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("ccbf")

add_executable("ccbf" "src/main.cpp")

set_property(TARGET "ccbf" PROPERTY CXX_EXTENSIONS ON)
set_property(TARGET "ccbf" PROPERTY CXX_STANDARD 26)

target_compile_options("ccbf" PRIVATE "-Wall" "-Werror" "-pedantic-errors")

include_directories(
    "${PROJECT_SOURCE_DIR}/libs/fmt/include"
)

add_subdirectory("${PROJECT_SOURCE_DIR}/libs/fmt")

target_link_libraries("ccbf" PRIVATE fmt::fmt)

project("ccbf-repl")

add_executable("ccbf-repl" "src/main-repl.cpp")

set_property(TARGET "ccbf-repl" PROPERTY CXX_EXTENSIONS ON)
set_property(TARGET "ccbf-repl" PROPERTY CXX_STANDARD 26)

target_compile_options("ccbf-repl" PRIVATE "-Wall" "-Werror" "-pedantic-errors")

target_link_libraries("ccbf-repl" PRIVATE fmt::fmt)
