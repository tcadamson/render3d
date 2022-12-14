# Cross-platform code courtesy of https://github.com/Polytonic/Glitter/blob/master/CMakeLists.txt
cmake_minimum_required(VERSION 3.23)
project(render3d)

set(CMAKE_CXX_STANDARD 14)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(lib/glfw/)
include_directories(lib/glfw/include/ lib/glad/include/ lib/stb/ lib/glm/)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

file(GLOB LIB_SOURCES lib/glad/src/glad.c)
file(GLOB PROJECT_SHADERS render3d/shaders/*.glsl)
file(GLOB PROJECT_TEXTURES render3d/textures/*.png)
file(GLOB PROJECT_HEADERS render3d/*.h)
file(GLOB PROJECT_SOURCES main.cpp render3d/*.cpp)
add_definitions(-DGLFW_INCLUDE_NONE)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_SHADERS} ${PROJECT_TEXTURES} ${LIB_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/render3d/shaders/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/render3d/shaders/
    DEPENDS ${PROJECT_SHADERS})
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/render3d/textures/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/render3d/textures/
    DEPENDS ${PROJECT_TEXTURES})
