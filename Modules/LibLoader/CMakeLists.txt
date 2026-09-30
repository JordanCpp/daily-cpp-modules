
cmake_minimum_required(VERSION 3.30)

add_library(LibLoader STATIC)

target_sources(LibLoader PUBLIC 
    FILE_SET CXX_MODULES FILES "LibLoader.cppm")

target_compile_features(LibLoader PUBLIC cxx_std_23)
target_include_directories(LibLoader INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
