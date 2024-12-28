cmake_minimum_required(VERSION 3.20)
project(RanokCAD)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(ThirdParty)

add_executable(RanokCAD
        ${RANOKCAD_THIRDPARTY_SOURCES}
        Source/Ranok.cpp
        Source/Window/Window.cpp
        Source/Window/Window.h
        Source/App/Application.cpp
        Source/App/Application.h
        Source/Types/MulticastDelegate.h
        Source/Opengl/GpuResource.cpp
        Source/Opengl/GpuResource.h
        Source/Opengl/GpuBuffer.cpp
        Source/Opengl/GpuBuffer.h
        Source/Opengl/GpuTexture.cpp
        Source/Opengl/GpuTexture.h
        Source/Language/ActionNode.h
        Source/Language/Token.h
        Source/Language/Parser.h
        Source/Language/Parser.cpp
        Source/Language/Lexer.h
        Source/Language/HardcodedConstructions.h
        Source/Language/Lexer.cpp
        Source/Language/HardcodedConstructions.cpp
        Source/Language/ActionTree.h
        Source/Language/ActionTree.cpp
        Source/Language/ActionNode.h
        Source/Language/ActionNode.cpp
        Source/Language/Generators/IGenerator.cpp
        Source/Language/Generators/IGenerator.h
        Source/Language/Generators/OpenclGenerator.cpp
        Source/Language/Generators/OpenclGenerator.h
        Source/Language/Generators/ShaderGenerator.cpp
        Source/Language/Generators/ShaderGenerator.h
        Source/ClKernel/ClExecutor.cpp
        Source/ClKernel/ClExecutor.h
        Source/ClKernel/MultiDimSpace.cpp
        Source/ClKernel/MultiDimSpace.h
        Source/ClKernel/FlatBuffer.cpp
        Source/ClKernel/FlatBuffer.h
        Source/Cli/AppArgs.cpp
        Source/Cli/AppArgs.h
)

target_link_libraries(RanokCAD PRIVATE RanokCADThirdParty)

# System libs
find_package(OpenGL REQUIRED)
target_link_libraries(RanokCAD PRIVATE OpenGL::GL)
find_package(OpenCL REQUIRED)
target_link_libraries(RanokCAD PRIVATE OpenCL::OpenCL)