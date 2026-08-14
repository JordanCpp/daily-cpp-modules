


cmake_minimum_required(VERSION 3.28)
project(DailyCppModulesExamples LANGUAGES CXX)

set(TARGET_NAMES
    BmpTest
    MorphingJuliaFractal
    RetroTunnelEffect
    RenderPixels1
    RenderPixels2
    StarfieldSimulation
)

foreach(TARGET_NAME IN LISTS TARGET_NAMES)
    add_executable(${TARGET_NAME} "${TARGET_NAME}.cpp")
    target_link_libraries(${TARGET_NAME} PRIVATE Painter GlmLite WinLite OpenGL FpsCounter BmpLoader)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif()
endforeach()

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/files" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
