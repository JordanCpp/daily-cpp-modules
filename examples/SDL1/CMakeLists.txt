
cmake_minimum_required(VERSION 3.30)
project(SDL1Examples LANGUAGES CXX)

set(TARGET_NAMES
    SDL1_Cube3D
    SDL1_DiamondSquarePlasma
    SDL1_DissolveEffect
    SDL1_DistortionPortal
    SDL1_Fire
    SDL1_FractalFern
    SDL1_GameOfLife
    SDL1_InputAndRendering
    SDL1_LensEffect
    SDL1_LightTunnel
    SDL1_Mandelbrot
    SDL1_MatrixRain
    SDL1_MazeGenerator
    SDL1_MetaBalls
    SDL1_Particles
    SDL1_RetroPlasma
    SDL1_Starfield
    SDL1_Tunnel
    SDL1_VoxelLandscape
    SDL1_WaterRipples
    SDL1_Window
    SDL1_Wobble)

foreach(TARGET_NAME IN LISTS TARGET_NAMES)
    add_executable(${TARGET_NAME} "${TARGET_NAME}.cpp")

    target_link_libraries(${TARGET_NAME} PRIVATE SDL1.API SDL1.Loader)

    target_compile_options(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_OPTIONS})
    target_compile_definitions(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif()
endforeach()
