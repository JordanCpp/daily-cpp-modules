
cmake_minimum_required(VERSION 3.30)

add_library(GlmLite STATIC)

target_sources(GlmLite PUBLIC 
    FILE_SET CXX_MODULES FILES "GlmLite.ixx"
)

target_compile_features(GlmLite PUBLIC cxx_std_23)
target_include_directories(GlmLite INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
