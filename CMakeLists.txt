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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/package)

find_package(PkgConfig REQUIRED) 

pkg_check_modules(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE LIBS_FILES "libs/*.cpp")
include_directories(PUBLIC libs)
add_executable(${PROJECT_NAME} "libs/glad/src/glad.c" ${SOURCE_FILES} ${LIBS_FILES} "src/main.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ${M_CPP_17_COMPILER_FLAG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"libs/amd_tressfx/include\"")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows") 
    target_link_libraries(${PROJECT_NAME} ${M_ADDITIONAL_LIBS} SDL2 
    stdc++ ole32 user32 gdi32 dinput8 shell32 setupapi advapi32 uuid version oleaut32 ole32 imm32 winmm gdi32 user32 m)
else()
    target_link_libraries(${PROJECT_NAME} ${M_ADDITIONAL_LIBS} SDL2 ${CMAKE_DL_LIBS} )
endif()
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

include_directories(PUBLIC "$ENV{homepath}/scoop/apps/sdl2/current/include")

include_directories(PUBLIC libs/glm)
include_directories(PUBLIC libs/glm/glm)
include_directories(PUBLIC libs/glad/include)
include_directories(PUBLIC libs/amd_tressfx/include)
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "/usr/x86_64-w64-mingw32/sys-root/mingw/bin/SDL2.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "/usr/x86_64-w64-mingw32/sys-root/mingw/bin/libgcc_s_seh-1.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "/usr/x86_64-w64-mingw32/sys-root/mingw/bin/libstdc++-6.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
        add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "/usr/x86_64-w64-mingw32/sys-root/mingw/bin/libwinpthread-1.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} DESTINATION ${CMAKE_BUILD_DIRECTORY}/package)