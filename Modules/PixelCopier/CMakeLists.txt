
cmake_minimum_required(VERSION 3.30)

add_library(PixelCopier STATIC)

target_sources(PixelCopier PUBLIC 
    FILE_SET CXX_MODULES FILES "PixelCopier.ixx"
)

target_compile_features(PixelCopier PUBLIC cxx_std_23)
target_include_directories(PixelCopier INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
