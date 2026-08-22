cmake_minimum_required(VERSION 3.28)

project(HighResTimer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(HighResTimer)

target_sources(HighResTimer PUBLIC FILE_SET CXX_MODULES FILES "HighResTimer.ixx")

target_include_directories(HighResTimer INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
