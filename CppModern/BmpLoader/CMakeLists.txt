
cmake_minimum_required(VERSION 3.28)

project(BmpLoader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(BmpLoader)

target_sources(BmpLoader PUBLIC FILE_SET CXX_MODULES FILES "BmpLoader.ixx")

target_include_directories(BmpLoader INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
