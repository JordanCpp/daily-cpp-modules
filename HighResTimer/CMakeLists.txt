
cmake_minimum_required(VERSION 3.30)

add_library(HighResTimer STATIC)

target_sources(HighResTimer PUBLIC 
    FILE_SET CXX_MODULES FILES "HighResTimer.ixx"
)

target_include_directories(HighResTimer INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_compile_options(HighResTimer PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(HighResTimer PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
