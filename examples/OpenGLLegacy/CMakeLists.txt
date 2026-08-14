
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

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif()
endforeach()
