cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

get_filename_component(RootDirName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${RootDirName} LANGUAGES CXX)

# Source files
file(GLOB_RECURSE PROJECT_SOURCES
    ${PROJECT_NAME}/*.cpp
    ${PROJECT_NAME}/*.h
    ${PROJECT_NAME}/*.hpp)

set(PROJECT_SOURCES ${PROJECT_SOURCES}
    ImGui/imgui.cpp
    ImGui/imgui_draw.cpp
    ImGui/imgui_tables.cpp
    ImGui/imgui_widgets.cpp
    # SDL2+OpenGL-specific files
    ImGui/backends/imgui_impl_sdl2.cpp
    ImGui/backends/imgui_impl_opengl3.cpp)


add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}
    ImGui
    ImGui/backends)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::GLEW)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
