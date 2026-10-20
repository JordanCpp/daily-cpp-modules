
cmake_minimum_required(VERSION 3.30)

add_library(GlutLite STATIC)

target_sources(GlutLite PUBLIC 
    FILE_SET CXX_MODULES FILES "GlutLite.cppm"
)

target_link_libraries(GlutLite PUBLIC OpenGL WinLite)
target_compile_features(GlutLite PUBLIC cxx_std_23)
target_include_directories(GlutLite INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
