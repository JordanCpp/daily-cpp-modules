
cmake_minimum_required(VERSION 3.30)
project(SDL1Examples LANGUAGES CXX)

set(TARGET_NAMES
    SDL2_Attractor
    SDL2_AutonomousAgents
    SDL2_BarnsleyFern
    SDL2_ColorWave
    SDL2_CrystalGrowth
    SDL2_DelaunayTriangulation
    SDL2_ElasticGrid
    SDL2_EpicyclesFourier
    SDL2_InverseKinematics
    SDL2_Lissajous
    SDL2_PhysarumSim
    SDL2_Raycaster3D
    SDL2_RaymarchedClouds
    SDL2_RaymarchedMetaballs
    SDL2_SoftBodyPhysics
    SDL2_VerletCloth
    SDL2_WaveEquation
    SDL2_Window)

foreach(TARGET_NAME IN LISTS TARGET_NAMES)
    add_executable(${TARGET_NAME} "${TARGET_NAME}.cpp")

    target_link_libraries(${TARGET_NAME} PRIVATE SDL2.API SDL2.Loader)

    target_compile_options(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_OPTIONS})
    target_compile_definitions(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif()
endforeach()
