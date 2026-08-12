
cmake_minimum_required(VERSION 3.28)

project(Painter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Painter)

target_sources(Painter PUBLIC FILE_SET CXX_MODULES FILES "Painter.ixx" )

target_include_directories(Painter INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
