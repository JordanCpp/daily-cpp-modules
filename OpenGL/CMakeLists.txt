
cmake_minimum_required(VERSION 4.4)

add_library(OpenGL STATIC)

target_sources(OpenGL PUBLIC 
    FILE_SET CXX_MODULES FILES "OpenGL.ixx"
)

target_include_directories(OpenGL INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_compile_options(OpenGL PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(OpenGL PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
