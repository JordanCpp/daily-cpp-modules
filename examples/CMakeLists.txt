
cmake_minimum_required(VERSION 3.28)
project(DailyCppModulesExamples LANGUAGES CXX)

add_executable(GL1 "GL1.cpp")
target_link_libraries(GL1 PRIVATE WinLite OpenGL FpsCounter;)

add_executable(BmpTest "BmpTest.cpp")
target_link_libraries(BmpTest PRIVATE WinLite Painter BmpLoader FpsCounter)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(GL1 PRIVATE stdc++exp)
    target_link_libraries(BmpTest PRIVATE stdc++exp)
endif()

add_executable(RenderPixels1 "RenderPixels1.cpp")
target_link_libraries(RenderPixels1 PRIVATE WinLite Painter)

add_executable(RenderPixels2 "RenderPixels2.cpp")
target_link_libraries(RenderPixels2 PRIVATE WinLite Painter)

add_executable(StarfieldSimulation "StarfieldSimulation.cpp")
target_link_libraries(StarfieldSimulation PRIVATE WinLite Painter)

add_executable(RetroTunnelEffect "RetroTunnelEffect.cpp")
target_link_libraries(RetroTunnelEffect PRIVATE WinLite Painter)

add_executable(MorphingJuliaFractal "MorphingJuliaFractal.cpp")
target_link_libraries(MorphingJuliaFractal PRIVATE WinLite Painter)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/files" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}") 