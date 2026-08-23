
cmake_minimum_required(VERSION 4.4)

# Инициализируем проект модуля. Имя 'WinLite' автоматически запишется в ${PROJECT_NAME}
project(WinLite LANGUAGES CXX)

# Создаем статическую библиотеку
add_library(${PROJECT_NAME} STATIC)

# Разделение файлов по операционным системам
if(WIN32)
    set(OS_SPECIFIC_MODULES 
        "WinLite.MainWindow.WinNt.ixx"
        "WinLite.SoftwareWindow.Win.ixx"
        "WinLite.OpenGL1Window.Win.ixx"
    )
    # Системная линковка OpenGL, необходимая для Windows-сборок
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
else()
    set(OS_SPECIFIC_MODULES
        "WinLite.MainWindow.Linux.ixx"
        "WinLite.SoftwareWindow.Linux.ixx"
    )
endif()

# Регистрируем все файлы интерфейсов C++ модулей в единый FILE_SET
target_sources(${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES 
    "WinLite.ixx"
    "WinLite.KeyEnums.ixx"
    "WinLite.KeyMapper.ixx"
    "WinLite.Events.ixx"
    "WinLite.Queue.ixx" 
    ${OS_SPECIFIC_MODULES}
)

# Настройка путей для поиска интерфейсов модулей
target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

# Автоматически наследуем параноидальные флаги безопасности из корня репозитория
target_compile_options(${PROJECT_NAME} PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
