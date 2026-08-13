cmake_minimum_required(VERSION 3.28)

project(FpsCounter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(FpsCounter)

target_sources(FpsCounter PUBLIC FILE_SET CXX_MODULES FILES "FpsCounter.ixx")

target_include_directories(FpsCounter INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
