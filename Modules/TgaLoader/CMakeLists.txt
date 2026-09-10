
cmake_minimum_required(VERSION 3.30)

add_library(TgaLoader STATIC)

target_sources(TgaLoader PUBLIC 
    FILE_SET CXX_MODULES FILES "TgaLoader.ixx"
)

target_compile_features(TgaLoader PUBLIC cxx_std_23)
target_include_directories(TgaLoader INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
