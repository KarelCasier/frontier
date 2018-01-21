cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(frontier VERSION 0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(CMAKE_CXX_FLAGS_DEBUG "-g" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3" CACHE INTERNAL "" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(frontier)
add_subdirectory(navigation)
add_subdirectory(texture_manager)
add_subdirectory(utils)
