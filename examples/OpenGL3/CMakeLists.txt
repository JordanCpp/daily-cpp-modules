
cmake_minimum_required(VERSION 3.30)
project(OpenGLLegacyExamples LANGUAGES CXX)

cmake_minimum_required(VERSION 3.30)
project(OpenGLLegacyExamples LANGUAGES CXX)

set(TARGET_NAMES
    GL3_LiquidMirrorOcean
    GL3_NeonTunnel
    GL3_PlasmaSphere
    GL3_RaymarchingSDF
    GL3_Triangle)

foreach(TARGET_NAME IN LISTS TARGET_NAMES)
    add_executable(${TARGET_NAME} "${TARGET_NAME}.cpp")

    target_link_libraries(${TARGET_NAME} PRIVATE GlmLite WinLite OpenGL FpsCounter)

    target_sources(${TARGET_NAME} PUBLIC FILE_SET CXX_MODULES FILES "AppGL3.ixx")

    target_compile_options(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_OPTIONS})
    target_compile_definitions(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif()
endforeach()
