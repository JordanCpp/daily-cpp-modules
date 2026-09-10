
cmake_minimum_required(VERSION 3.30)

add_library(BmpLoader STATIC)

target_sources(BmpLoader PUBLIC 
    FILE_SET CXX_MODULES FILES "BmpLoader.ixx"
)

target_compile_features(BmpLoader PUBLIC cxx_std_23)
target_include_directories(BmpLoader INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
