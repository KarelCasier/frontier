cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(frontier VERSION 0.1 LANGUAGES CXX)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(CMAKE_CXX_FLAGS_DEBUG "-g" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3" CACHE INTERNAL "" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(frontier)
add_subdirectory(navigation)
