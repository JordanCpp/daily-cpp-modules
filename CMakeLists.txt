
cmake_minimum_required(VERSION 3.28)
project(DailyCppModules LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB sub_directories RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */CMakeLists.txt)

foreach(dir_path ${sub_directories})
    get_filename_component(module_name ${dir_path} DIRECTORY)
    
    if(module_name MATCHES "^(build|cmake-build)")
        continue()
    endif()

    message(STATUS "Found module: ${module_name}")

    add_subdirectory(${module_name})

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${module_name}/main.cpp")
        set(test_target "test_${module_name}")
        
        add_executable(${test_target} ${module_name}/main.cpp)
        
        target_link_libraries(${test_target} PRIVATE ${module_name})
    endif()

endforeach()
