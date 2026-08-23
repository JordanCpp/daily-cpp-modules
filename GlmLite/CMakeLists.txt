
cmake_minimum_required(VERSION 4.3)

add_library(GlmLite STATIC)

target_sources(GlmLite PUBLIC 
    FILE_SET CXX_MODULES FILES "GlmLite.ixx"
)

target_include_directories(GlmLite INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_compile_options(GlmLite PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(GlmLite PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
