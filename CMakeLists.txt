cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_TOOLCHAIN_FILE vcpkg/scripts/buildsystems/vcpkg.cmake)

get_filename_component(RootDirName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${RootDirName} LANGUAGES CXX)

add_subdirectory(ThirdParty)
add_subdirectory(RanokCAD)
add_subdirectory(RanokLang)
add_subdirectory(ResourceManager)
add_subdirectory(OpenglWrap)

if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
    add_custom_target(compile_commands_link ALL
        COMMAND ${CMAKE_COMMAND} -E create_hardlink ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
endif()