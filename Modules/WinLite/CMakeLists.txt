
cmake_minimum_required(VERSION 3.30)

project(WinLite LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

if(WIN32)
    set(OS_SPECIFIC_MODULES 
        "WinLite.MainWindow.WinNt.cppm"
        "WinLite.SoftwareWindow.Win.cppm"
        "WinLite.OpenGL1Window.Win.cppm"
        "WinLite.OpenGL3Window.Win.cppm"
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
else()
    set(OS_SPECIFIC_MODULES
        "WinLite.MainWindow.XLib.cppm"
        "WinLite.SoftwareWindow.XLib.cppm"
        "WinLite.OpenGL1Window.XLib.cppm"
        "WinLite.OpenGL3Window.XLib.cppm"
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE GL X11)
endif()

target_sources(${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES 
    "WinLite.cppm"
    "WinLite.KeyEnums.cppm"
    "WinLite.KeyMapper.cppm"
    "WinLite.Events.cppm"
    "WinLite.Queue.cppm" 
    ${OS_SPECIFIC_MODULES}
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
