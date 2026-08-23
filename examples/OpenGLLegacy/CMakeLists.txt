
cmake_minimum_required(VERSION 4.3)
project(OpenGLLegacyExamples LANGUAGES CXX)

add_library(AppGL1 STATIC)
target_sources(AppGL1 PUBLIC 
    FILE_SET CXX_MODULES FILES "AppGL1.ixx"
)

target_link_libraries(AppGL1 PUBLIC GlmLite WinLite OpenGL FpsCounter)
target_compile_options(AppGL1 PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(AppGL1 PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

set(TARGET_NAMES
    AnimatedWave
    RotatingCube
    Triangle
    StencilMirrorReflection
    HeightFog
    RotatingPlanet
)

foreach(TARGET_NAME IN LISTS TARGET_NAMES)
    add_executable(${TARGET_NAME} "${TARGET_NAME}.cpp")

    target_link_libraries(${TARGET_NAME} PRIVATE AppGL1)

    target_compile_options(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_OPTIONS})
    target_compile_definitions(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif()
endforeach()
