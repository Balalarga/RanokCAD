cmake_minimum_required(VERSION 3.28)
project(Ranok3)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ranok3
        Source/Ranok3.cpp
        Source/Window/Window.cpp
        Source/Window/Window.h
        Source/App/Application.cpp
        Source/App/Application.h
)

find_package(OpenGL REQUIRED)
target_link_libraries(Ranok3 PRIVATE OpenGL::GL)

find_package(GLEW REQUIRED)
target_link_libraries(Ranok3 PRIVATE GLEW::GLEW)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Ranok3 PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(Ranok3 PRIVATE imgui::imgui)

find_package(implot CONFIG REQUIRED)
target_link_libraries(Ranok3 PRIVATE implot::implot)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Ranok3 PRIVATE nlohmann_json::nlohmann_json)

find_package(OpenCL REQUIRED)
target_link_libraries(Ranok3 PRIVATE OpenCL::OpenCL)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(Ranok3 PRIVATE spdlog::spdlog)

find_package(glm CONFIG REQUIRED)
target_link_libraries(Ranok3 PRIVATE glm::glm-header-only)
