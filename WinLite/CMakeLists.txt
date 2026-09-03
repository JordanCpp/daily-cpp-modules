
cmake_minimum_required(VERSION 3.30)

project(WinLite LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

if(WIN32)
    set(OS_SPECIFIC_MODULES 
        "WinLite.MainWindow.WinNt.ixx"
        "WinLite.SoftwareWindow.Win.ixx"
        "WinLite.OpenGL1Window.Win.ixx"
        "WinLite.OpenGL3Window.Win.ixx"
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
else()
    set(OS_SPECIFIC_MODULES
        "WinLite.MainWindow.Linux.ixx"
        "WinLite.SoftwareWindow.Linux.ixx"
    )
endif()

target_sources(${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES 
    "WinLite.ixx"
    "WinLite.KeyEnums.ixx"
    "WinLite.KeyMapper.ixx"
    "WinLite.Events.ixx"
    "WinLite.Queue.ixx" 
    ${OS_SPECIFIC_MODULES}
)

target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_compile_options(${PROJECT_NAME} PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
