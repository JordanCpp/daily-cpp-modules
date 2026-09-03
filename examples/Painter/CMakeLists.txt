
cmake_minimum_required(VERSION 3.30)
project(PainterExamples LANGUAGES CXX)

add_library(AppPainter STATIC)
target_sources(AppPainter PUBLIC 
    FILE_SET CXX_MODULES FILES "App.ixx"
)

target_link_libraries(AppPainter PUBLIC 
    HighResTimer 
    PixelPainter 
    PixelCopier 
    GlmLite 
    WinLite 
    OpenGL 
    FpsCounter 
    BmpLoader
    BmpSaver
)

target_compile_options(AppPainter PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(AppPainter PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

set(TARGET_NAMES
    CosmicPlasma
    StarfieldWarp
    CyberpunkMatrix
    AppTemplate
    SinePlasma
    3DHyperTunnel
    PlexusEffect
    LaserOscilloscope
    3DPointCloud
    FallingSand
    JuliaFractal
    TeslaLightning
    MagneticField
    SynthwaveTerrain
    RetroFireEffect
    WaterRipples
    BmpTest
    CyberpunkRetroGrid
    MandalaGenerator
    MorphingJuliaFractal
    RetroTunnelEffect
    EnhancedInteractive
    EnhancedDynamic
    StarfieldSimulation
)

foreach(TARGET_NAME IN LISTS TARGET_NAMES)
    add_executable(${TARGET_NAME} "${TARGET_NAME}.cpp")
    
    target_link_libraries(${TARGET_NAME} PRIVATE AppPainter)

    target_compile_options(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_OPTIONS})
    target_compile_definitions(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif()
endforeach()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/files")
    add_custom_target(CopyPainterAssets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/files"
            "${CMAKE_CURRENT_BINARY_DIR}/files"
        COMMENT "Updating painter assets (textures and BMP files) in binary directory..."
    )
endif()
