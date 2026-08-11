cmake_minimum_required(VERSION 3.28)

project(glm_lite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(glm_lite)

target_sources(glm_lite PUBLIC FILE_SET CXX_MODULES FILES "GlmLite.ixx")

target_include_directories(glm_lite INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
