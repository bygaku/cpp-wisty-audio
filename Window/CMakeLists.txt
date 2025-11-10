#== CMakeLists.txt ==#
cmake_minimum_required(VERSION 3.22)

#== Variables ==#
set(PROJECT_NAME "Window")
set(PROJECT_VER "0.1.0")

#== Project Definition ==#
project(${PROJECT_NAME} VERSION ${PROJECT_VER} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(IS_WIN32_APP OFF)

#== Source Files ==#
add_subdirectory(./src)        # Source files

#== Compiler Options ==#
if(MSVC)
    add_compile_options(/utf-8 /TP)
endif()
