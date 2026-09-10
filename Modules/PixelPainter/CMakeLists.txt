
cmake_minimum_required(VERSION 3.30)

add_library(PixelPainter STATIC)

target_sources(PixelPainter PUBLIC 
    FILE_SET CXX_MODULES FILES "PixelPainter.ixx"
)

target_compile_features(PixelPainter PUBLIC cxx_std_23)
target_include_directories(PixelPainter INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
