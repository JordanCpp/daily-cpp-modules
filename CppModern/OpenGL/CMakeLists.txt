
cmake_minimum_required(VERSION 3.28)

project(OpenGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(OpenGL)

target_sources(OpenGL PUBLIC FILE_SET CXX_MODULES FILES "OpenGL.ixx")

target_include_directories(OpenGL INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
