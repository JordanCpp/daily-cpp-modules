
cmake_minimum_required(VERSION 3.30)
project(OpenGLLegacyExamples LANGUAGES CXX)

add_library(AppGL3 STATIC)
target_sources(AppGL3 PUBLIC 
    FILE_SET CXX_MODULES FILES "AppGL3.ixx"
)

target_link_libraries(AppGL3 PUBLIC GlmLite WinLite OpenGL FpsCounter)
target_compile_options(AppGL3 PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(AppGL3 PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

set(TARGET_NAMES
    GL3_Triangle
)

foreach(TARGET_NAME IN LISTS TARGET_NAMES)
    add_executable(${TARGET_NAME} "${TARGET_NAME}.cpp")

    target_link_libraries(${TARGET_NAME} PRIVATE AppGL3)

    target_compile_options(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_OPTIONS})
    target_compile_definitions(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif()
endforeach()
