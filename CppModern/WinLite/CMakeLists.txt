
cmake_minimum_required(VERSION 3.28)

project(WinLite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(WinLite)

if(WIN32)
    set(MODULE_FILE 
    "WinLite.MainWindow.Win9x.ixx"
    "WinLite.SoftwareWindow.Win9x.ixx")
else()
    set(MODULE_FILE WinLite.MainWindow.Linux.ixx)
endif()

target_sources(WinLite PUBLIC FILE_SET CXX_MODULES FILES 
    "WinLite.ixx" 
    "WinLite.Events.ixx" 
    "WinLite.Queue.ixx" ${MODULE_FILE})

target_include_directories(WinLite INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
