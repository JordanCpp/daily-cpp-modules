
cmake_minimum_required(VERSION 3.30)

#SDL1.API
add_library               (SDL3.API STATIC)
target_sources            (SDL3.API PUBLIC FILE_SET CXX_MODULES FILES "SDL3.API.cppm")
target_compile_features   (SDL3.API PUBLIC cxx_std_23)
target_include_directories(SDL3.API INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

#SDL1.Loader
add_library               (SDL3.Loader  STATIC)
target_sources            (SDL3.Loader  PUBLIC FILE_SET CXX_MODULES FILES "SDL3.Loader.cppm")
target_link_libraries     (SDL3.Loader  PRIVATE LibLoader SDL3.API)
target_compile_features   (SDL3.Loader  PUBLIC cxx_std_23)
target_include_directories(SDL3.Loader  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
