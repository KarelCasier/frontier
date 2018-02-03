cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(frontier VERSION 0.1 LANGUAGES CXX)

add_subdirectory(ext/entityx EXCLUDE_FROM_ALL)
add_subdirectory(ext/tinyxml2 EXCLUDE_FROM_ALL)
add_subdirectory(ext/googletest EXCLUDE_FROM_ALL)

# Hacky way to remove external project tests
add_custom_target(exclude_entityx_tests ALL 
    COMMAND rm -f "ext/entityx/CTestTestfile.cmake")
add_custom_target(exclude_tinyxml2_lib_tests ALL 
    COMMAND rm -f "ext/tinyxml2/CTestTestfile.cmake")

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g3" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3" CACHE INTERNAL "" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(asset_managers)
add_subdirectory(frontier)
add_subdirectory(math)
add_subdirectory(utils)
