
cmake_minimum_required(VERSION 4.4)

add_library(PixelCopier STATIC)

target_sources(PixelCopier PUBLIC 
    FILE_SET CXX_MODULES FILES "PixelCopier.ixx"
)

target_include_directories(PixelCopier INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_compile_options(PixelCopier PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(PixelCopier PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
