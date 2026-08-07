
cmake_minimum_required(VERSION 3.28)
project(DailyCppModulesExamples LANGUAGES CXX)

add_executable(RenderPixels1 "RenderPixels1.cpp")
target_link_libraries(RenderPixels1 PRIVATE WinLite SoftwareRender)

add_executable(RenderPixels2 "RenderPixels2.cpp")
target_link_libraries(RenderPixels2 PRIVATE WinLite SoftwareRender)

add_executable(StarfieldSimulation "StarfieldSimulation.cpp")
target_link_libraries(StarfieldSimulation PRIVATE WinLite SoftwareRender)

add_executable(RetroTunnelEffect "RetroTunnelEffect.cpp")
target_link_libraries(RetroTunnelEffect PRIVATE WinLite SoftwareRender)

add_executable(MorphingJuliaFractal "MorphingJuliaFractal.cpp")
target_link_libraries(MorphingJuliaFractal PRIVATE WinLite SoftwareRender)
