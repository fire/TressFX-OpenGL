cmake_minimum_required(VERSION 3.0)
project(TressFx)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Utils.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

set_with_default(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")
assert_one_of(CMAKE_BUILD_TYPE Release Debug)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

message("CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message("Architecture: ${M_ARCH_NAME}")
message("Complier: ${M_COMPILER_NAME}")
message("Project: ${CMAKE_PROJECT_NAME} v${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE LIBS_FILES "libs/*.cpp")
include_directories(PUBLIC libs)
add_executable(${PROJECT_NAME} "libs/glad/src/glad.c" ${SOURCE_FILES} ${LIBS_FILES} "src/main.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ${M_CPP_17_COMPILER_FLAG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"libs/amd_tressfx/include\"")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D DEBUG -O0 -gdwarf-2") # flag for debug
endif()

target_link_libraries(${PROJECT_NAME} ${M_ADDITIONAL_LIBS})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

find_package(SDL2 REQUIRED)
include_directories(PUBLIC ${SDL2_INCLUDE_DIRS})

include_directories(PUBLIC libs/glm)
include_directories(PUBLIC libs/glm/glm)
include_directories(PUBLIC libs/glad/include)
include_directories(PUBLIC libs/amd_tressfx/include)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
