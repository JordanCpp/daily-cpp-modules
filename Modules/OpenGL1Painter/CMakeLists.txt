
cmake_minimum_required(VERSION 3.30)

add_library(OpenGL1Painter STATIC)

target_sources(OpenGL1Painter PUBLIC 
    FILE_SET CXX_MODULES FILES "OpenGL1Painter.ixx"
)

target_link_libraries(OpenGL1Painter PUBLIC OpenGL)
target_compile_features(OpenGL1Painter PUBLIC cxx_std_23)
target_include_directories(OpenGL1Painter INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
