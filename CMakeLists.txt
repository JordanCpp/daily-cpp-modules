cmake_minimum_required(VERSION 3.30)

if(WIN32)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
else()
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
endif()

project(DailyCppModules LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_MODULE_STD ON)

set(GLOBAL_COMPILE_OPTIONS "")
set(GLOBAL_COMPILE_DEFINITIONS "")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    list(APPEND GLOBAL_COMPILE_OPTIONS 
        -fmodules-ts
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Weffc++ 
        -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization 
        -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations 
        -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual 
        -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel 
        -Wstrict-overflow=2 -Wswitch-default -Wzero-as-null-pointer-constant 
        -fstack-protector-strong
        -Wno-system-headers
    )
    list(APPEND GLOBAL_COMPILE_DEFINITIONS _GLIBCXX_ASSERTIONS)
endif()

add_subdirectory(Modules)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples/CMakeLists.txt")
    add_subdirectory(examples)
endif()
