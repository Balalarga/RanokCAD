cmake_minimum_required(VERSION 3.28)
project(RanokCAD)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)

add_executable(RanokCAD
        Source/Ranok.cpp
        Source/Window/Window.cpp
        Source/Window/Window.h
        Source/App/Application.cpp
        Source/App/Application.h
)

find_package(OpenGL REQUIRED)
target_link_libraries(RanokCAD PRIVATE OpenGL::GL)

find_package(GLEW REQUIRED)
target_link_libraries(RanokCAD PRIVATE GLEW::GLEW)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(RanokCAD PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(RanokCAD PRIVATE imgui::imgui)

find_package(implot CONFIG REQUIRED)
target_link_libraries(RanokCAD PRIVATE implot::implot)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(RanokCAD PRIVATE nlohmann_json::nlohmann_json)

find_package(OpenCL REQUIRED)
target_link_libraries(RanokCAD PRIVATE OpenCL::OpenCL)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(RanokCAD PRIVATE spdlog::spdlog)

find_package(glm CONFIG REQUIRED)
target_link_libraries(RanokCAD PRIVATE glm::glm-header-only)
