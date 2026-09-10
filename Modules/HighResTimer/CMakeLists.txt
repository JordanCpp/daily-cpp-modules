
cmake_minimum_required(VERSION 3.30)

add_library(HighResTimer STATIC)

target_sources(HighResTimer PUBLIC 
    FILE_SET CXX_MODULES FILES "HighResTimer.ixx"
)

target_compile_features(HighResTimer PUBLIC cxx_std_23)
target_include_directories(HighResTimer INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
