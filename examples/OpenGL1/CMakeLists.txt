
cmake_minimum_required(VERSION 3.30)
project(OpenGLLegacyExamples LANGUAGES CXX)

add_library(AppGL1 STATIC)
target_sources(AppGL1 PUBLIC 
    FILE_SET CXX_MODULES FILES "AppGL1.ixx"
)

target_link_libraries(AppGL1 PUBLIC GlmLite WinLite OpenGL FpsCounter)
target_compile_options(AppGL1 PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(AppGL1 PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

set(TARGET_NAMES
    GL1_AnimatedWave
    GL1_EnvironmentMapping
    GL1_FractalCarpet
    GL1_HeightFog
    GL1_HolographicRadar
    GL1_KineticDNA
    GL1_LiquidMercuryMetaballs
    GL1_MirrorEqualizer
    GL1_ProjectiveStainedGlass
    GL1_RotatingCube
    GL1_RotatingPlanet
    GL1_SpecularDiscoBall
    GL1_StarfieldSpaceWarp
    GL1_StencilMirrorReflection
    GL1_SynthwaveGrid
    GL1_Triangle
    GL1_VectorXorExplosion
    GL1_XRayStencil
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
