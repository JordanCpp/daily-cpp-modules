
cmake_minimum_required(VERSION 3.28)

project(PixelCopier LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(PixelCopier)

target_sources(PixelCopier PUBLIC FILE_SET CXX_MODULES FILES "PixelCopier.ixx" )

target_include_directories(PixelCopier INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
