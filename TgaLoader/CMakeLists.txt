
cmake_minimum_required(VERSION 4.4)

add_library(TgaLoader STATIC)

target_sources(TgaLoader PUBLIC 
    FILE_SET CXX_MODULES FILES "TgaLoader.ixx"
)

target_include_directories(TgaLoader INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_compile_options(TgaLoader PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(TgaLoader PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
