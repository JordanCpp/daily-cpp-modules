
cmake_minimum_required(VERSION 3.30)

#SDL2.API
add_library               (SDL2.API STATIC)
target_sources            (SDL2.API PUBLIC FILE_SET CXX_MODULES FILES "SDL2.API.cppm")
target_compile_features   (SDL2.API PUBLIC cxx_std_23)
target_include_directories(SDL2.API INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

#SDL2.Loader
add_library               (SDL2.Loader  STATIC)
target_sources            (SDL2.Loader  PUBLIC FILE_SET CXX_MODULES FILES "SDL2.Loader.cppm")
target_link_libraries     (SDL2.Loader  PRIVATE LibLoader SDL2.API)
target_compile_features   (SDL2.Loader  PUBLIC cxx_std_23)
target_include_directories(SDL2.Loader  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
