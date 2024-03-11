cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

get_filename_component(RootDirName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${RootDirName} LANGUAGES CXX)

find_package(bgfx CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Source files
file(GLOB_RECURSE PROJECT_SOURCES
    ${PROJECT_NAME}/*.cpp
    ${PROJECT_NAME}/*.h
    ${PROJECT_NAME}/*.hpp
    Assets/*
    *.json)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY
             MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_property(TARGET ${PROJECT_NAME} PROPERTY WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
#set_target_properties(${PROJECT_NAME} PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
    RanokLang
    nlohmann_json::nlohmann_json
    imgui::imgui
    glfw
    bgfx::bx
    bgfx::bgfx
    bgfx::bimg
    bgfx::bimg_decode
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}/${PROJECT_NAME})
