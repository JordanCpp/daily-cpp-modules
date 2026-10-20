
cmake_minimum_required(VERSION 3.30)

set(TARGET_NAMES
    Bounce
    GlutLite_Triangle)

foreach(TARGET_NAME IN LISTS TARGET_NAMES)
    add_executable(${TARGET_NAME} "${TARGET_NAME}.cpp")

    target_link_libraries(${TARGET_NAME} PRIVATE GlutLite OpenGL)

    target_compile_options(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_OPTIONS})
    target_compile_definitions(${TARGET_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif()
endforeach()
