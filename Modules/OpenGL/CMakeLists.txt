
cmake_minimum_required(VERSION 3.30)

add_library(OpenGL STATIC)

target_sources(OpenGL PUBLIC 
    FILE_SET CXX_MODULES FILES "OpenGL.ixx"
)

target_compile_features(OpenGL PUBLIC cxx_std_23)
target_include_directories(OpenGL INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
