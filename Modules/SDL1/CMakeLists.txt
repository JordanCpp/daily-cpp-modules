
cmake_minimum_required(VERSION 3.30)

#SDL1.API
add_library               (SDL1.API STATIC)
target_sources            (SDL1.API PUBLIC FILE_SET CXX_MODULES FILES "SDL1.API.cppm")
target_compile_features   (SDL1.API PUBLIC cxx_std_23)
target_include_directories(SDL1.API INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

#SDL1.Loader
add_library               (SDL1.Loader  STATIC)
target_sources            (SDL1.Loader  PUBLIC FILE_SET CXX_MODULES FILES "SDL1.Loader.cppm")
target_link_libraries     (SDL1.Loader  PRIVATE LibLoader SDL1.API)
target_compile_features   (SDL1.Loader  PUBLIC cxx_std_23)
target_include_directories(SDL1.Loader  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
