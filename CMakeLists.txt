cmake_minimum_required(VERSION "3.28.3")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# INFO: ENABLE FOR RAYLIB GAME DEV
#
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,windows")

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
