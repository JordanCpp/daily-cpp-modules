
cmake_minimum_required(VERSION 3.30)

add_library(BmpSaver STATIC)

target_sources(BmpSaver PUBLIC 
    FILE_SET CXX_MODULES FILES " BmpSaver.ixx"
)

target_include_directories(BmpSaver INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_compile_options(BmpSaver PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(BmpSaver PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
