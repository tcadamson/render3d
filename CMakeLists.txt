cmake_minimum_required(VERSION 3.23)
project (render3d)

set(CMAKE_CXX_STANDARD 14)

# GLFW + GLAD + OpenGL config
# Cross-platform code courtesy of https://github.com/juliettef/GLFW-CMake-starter/blob/main/CMakeLists.txt
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} lib/glad/include)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")
add_subdirectory(lib/glfw)

if(MSVC)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

set(RENDER3D_ENTRY main.cpp)
add_executable(render3d #[[WIN32]] ${RENDER3D_ENTRY} lib/glad/src/glad.c)
target_link_libraries(render3d ${OPENGL_LIBRARIES} glfw)

if(MSVC)
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message("\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'render3d' as StartUp Project in Visual Studio\n")
    else()
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT render3d)
    endif()
endif()
