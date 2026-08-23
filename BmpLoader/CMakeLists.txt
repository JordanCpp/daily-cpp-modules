
cmake_minimum_required(VERSION 4.3)

add_library(BmpLoader STATIC)

target_sources(BmpLoader PUBLIC 
    FILE_SET CXX_MODULES FILES "BmpLoader.ixx"
)

target_include_directories(BmpLoader INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_compile_options(BmpLoader PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(BmpLoader PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
