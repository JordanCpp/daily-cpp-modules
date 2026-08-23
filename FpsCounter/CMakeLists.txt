
cmake_minimum_required(VERSION 4.4)

add_library(FpsCounter STATIC)

target_sources(FpsCounter PUBLIC 
    FILE_SET CXX_MODULES FILES "FpsCounter.ixx"
)

target_include_directories(FpsCounter INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_compile_options(FpsCounter PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(FpsCounter PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
