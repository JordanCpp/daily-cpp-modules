
cmake_minimum_required(VERSION 3.28)

project(PixelPainter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(PixelPainter)

target_sources(PixelPainter PUBLIC FILE_SET CXX_MODULES FILES "PixelPainter.ixx" )

target_include_directories(PixelPainter INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
