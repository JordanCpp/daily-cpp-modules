
cmake_minimum_required(VERSION 3.30)

add_library(FpsCounter STATIC)

target_sources(FpsCounter PUBLIC 
    FILE_SET CXX_MODULES FILES "FpsCounter.ixx"
)

target_compile_features(FpsCounter PUBLIC cxx_std_23)
target_include_directories(FpsCounter INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
