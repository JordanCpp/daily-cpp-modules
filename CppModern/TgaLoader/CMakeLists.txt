
cmake_minimum_required(VERSION 3.28)

project(TgaLoader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(TgaLoader)

target_sources(TgaLoader PUBLIC FILE_SET CXX_MODULES FILES "TgaLoader.ixx")

target_include_directories(TgaLoader INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
