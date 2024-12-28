cmake_minimum_required(VERSION 3.20)


set(RANOKCAD_THIRDPARTY_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/imgui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/imgui.h
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/imgui_demo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/imgui_internal.h
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/imgui_tables.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/imgui_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/imstb_rectpack.h
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/imstb_textedit.h
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/imstb_truetype.h
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/backends/imgui_impl_glfw.h
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/backends/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_LIST_DIR}/ImGui/backends/imgui_impl_opengl3.cpp
    PARENT_SCOPE
)

add_library(RanokCADThirdParty INTERFACE)

target_compile_definitions(RanokCADThirdParty INTERFACE GLEW_STATIC)
target_include_directories(RanokCADThirdParty INTERFACE ImGui)

add_subdirectory(GLFW3.4)
add_subdirectory(spdlog)
add_subdirectory(nlohmann_json)
add_subdirectory(glm)
add_subdirectory(argparse)

target_link_libraries(RanokCADThirdParty INTERFACE glfw)
target_link_libraries(RanokCADThirdParty INTERFACE nlohmann_json::nlohmann_json)
target_link_libraries(RanokCADThirdParty INTERFACE spdlog::spdlog)
target_link_libraries(RanokCADThirdParty INTERFACE argparse::argparse)
target_link_libraries(RanokCADThirdParty INTERFACE glm::glm-header-only)

# GLEW setup
target_link_directories(RanokCADThirdParty INTERFACE GLEW/lib/Release/x64)
target_link_libraries(RanokCADThirdParty INTERFACE glew32s.lib)
target_include_directories(RanokCADThirdParty INTERFACE GLEW/include)