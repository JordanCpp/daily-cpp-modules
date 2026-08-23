
cmake_minimum_required(VERSION 4.4)
project(OpenGLLegacyExamples LANGUAGES CXX)

# 1. Создаем общую локальную библиотеку для разделяемого модуля приложения
add_library(AppGL1 STATIC)
target_sources(AppGL1 PUBLIC 
    FILE_SET CXX_MODULES FILES "AppGL1.ixx"
)
# Привязываем к модулю приложения основные зависимости
target_link_libraries(AppGL1 PUBLIC GlmLite WinLite OpenGL FpsCounter)
target_compile_options(AppGL1 PRIVATE ${GLOBAL_COMPILE_OPTIONS})
target_compile_definitions(AppGL1 PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

# 2. Список ваших графических демо-сцен
set(TARGET_NAMES
    AnimatedWave
    RotatingCube
    Triangle
    StencilMirrorReflection
    HeightFog
    RotatingPlanet
)

# 3. Автоматически собираем каждый пример
foreach(TARGET_NAME IN LISTS TARGET_NAMES)
    # Создаем исполняемый файл из соответствующего .cpp
    add_executable(${TARGET_NAME} "${TARGET_NAME}.cpp")
    
    # Линкуем пример с нашим модулем приложения (он автоматически подтянет WinLite, GLM и т.д.)
    target_link_libraries(${TARGET_NAME} PRIVATE AppGL1)

    # Применяем ваши глобальные миссии-критические флаги к примерам
    target_compile_options(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_OPTIONS})
    target_compile_definitions(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

    # Специфичный для экспериментальных модулей GCC линковочный флаг
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif()
endforeach()
