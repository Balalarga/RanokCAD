cmake_minimum_required(VERSION 3.20)

add_library(Core STATIC
	Window/Window.cpp
	Window/Window.h
	App/Application.cpp
	App/Application.h
	Types/MulticastDelegate.h
	Opengl/GpuResource.cpp
	Opengl/GpuResource.h
	Opengl/GpuBuffer.cpp
	Opengl/GpuBuffer.h
	Opengl/GpuTexture.cpp
	Opengl/GpuTexture.h
	Language/ActionNode.h
	Language/Token.h
	Language/Parser.h
	Language/Parser.cpp
	Language/Lexer.h
	Language/HardcodedConstructions.h
	Language/Lexer.cpp
	Language/HardcodedConstructions.cpp
	Language/ActionTree.h
	Language/ActionTree.cpp
	Language/ActionNode.h
	Language/ActionNode.cpp
	Language/Generators/IGenerator.cpp
	Language/Generators/IGenerator.h
	Language/Generators/OpenclGenerator.cpp
	Language/Generators/OpenclGenerator.h
	Language/Generators/ShaderGenerator.cpp
	Language/Generators/ShaderGenerator.h
	ClKernel/ClExecutor.cpp
	ClKernel/ClExecutor.h
	ClKernel/MultiDimSpace.cpp
	ClKernel/MultiDimSpace.h
	ClKernel/FlatBuffer.cpp
	ClKernel/FlatBuffer.h
	Cli/AppArgs.cpp
	Cli/AppArgs.h
	ConfigManager.cpp
	ConfigManager.h
	Opengl/GpuShader.cpp
	Opengl/GpuShader.h
	Opengl/GpuShaderProgram.cpp
	Opengl/GpuShaderProgram.h
)
add_library(RanokCAD::Core ALIAS Core)
target_include_directories(Core PUBLIC .)


# System libs
find_package(OpenGL REQUIRED)
target_link_libraries(Core PUBLIC OpenGL::GL)
find_package(OpenCL REQUIRED)
target_link_libraries(Core PUBLIC OpenCL::OpenCL)


find_package(ImGui REQUIRED)
target_link_libraries(Core PUBLIC imgui::imgui)

find_package(GLEW REQUIRED)
target_link_libraries(Core PUBLIC GLEW::GLEW)
find_package(glfw3 REQUIRED)
target_link_libraries(Core PUBLIC glfw)
find_package(nlohmann_json REQUIRED)
target_link_libraries(Core PUBLIC nlohmann_json::nlohmann_json)
find_package(spdlog REQUIRED)
target_link_libraries(Core PUBLIC spdlog::spdlog)
find_package(argparse REQUIRED)
target_link_libraries(Core PUBLIC argparse::argparse)
find_package(glm REQUIRED)
target_link_libraries(Core PUBLIC glm::glm-header-only)
