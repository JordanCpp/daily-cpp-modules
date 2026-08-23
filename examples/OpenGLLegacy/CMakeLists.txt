
cmake_minimum_required(VERSION 3.28)
project(DailyCppModulesExamples LANGUAGES CXX)

set(TARGET_NAMES
    AnimatedWave
    RotatingCube
    Triangle
)

foreach(TARGET_NAME IN LISTS TARGET_NAMES)
    add_executable(${TARGET_NAME} "${TARGET_NAME}.cpp")
    target_link_libraries(${TARGET_NAME} PRIVATE GlmLite WinLite OpenGL FpsCounter)

    target_sources(${TARGET_NAME} PUBLIC FILE_SET CXX_MODULES FILES "AppGL1.ixx")

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif()
endforeach()
