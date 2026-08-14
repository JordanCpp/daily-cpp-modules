cmake_minimum_required(VERSION 3.28)

project(GlmLite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(GlmLite)

target_sources(GlmLite PUBLIC FILE_SET CXX_MODULES FILES "GlmLite.ixx")

target_include_directories(GlmLite INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
