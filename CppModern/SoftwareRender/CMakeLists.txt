
cmake_minimum_required(VERSION 3.28)

project(SoftwareRender LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(SoftwareRender)

target_sources(SoftwareRender PUBLIC FILE_SET CXX_MODULES FILES "SoftwareRender.ixx" )

target_include_directories(SoftwareRender INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
