#include "RanokCADApp.h"
#include <iostream>

#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include "bgfx/bgfx.h"


void error_callback(int error_code, const char* description)
{
	std::cerr << "GLFW error(" << error_code << "): " << description << std::endl;
}


static std::unique_ptr<RanokCADApp> sApplicationSingleton = nullptr;

RanokCADApp::RanokCADApp(const Params& params): _params(params)
{
	// constexpr auto resourceRegistry = "resourceRegistry.json";
	// if (!RanokResources::Get().InitFrom(resourceRegistry))
	// {
	// 	std::cout << "Couldn't read " << resourceRegistry << std::endl;
	// 	return -1;
	// }

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		throw std::runtime_error("Cannot initialize glfw3 library");
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	_window = glfwCreateWindow(_params.width, _params.height, "RanokCAD", 0, 0);

	bgfx::Init bgfxInit;
	bgfxInit.platformData.nwh = glfwGetWin32Window(_window);
	bgfxInit.type = bgfx::RendererType::Count;
	bgfxInit.resolution.width = _params.width;
	bgfxInit.resolution.height = _params.height;
	bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
	if (!bgfx::init(bgfxInit))
		throw std::runtime_error("Cannot initialize bgfx library");

	glfwSetKeyCallback(_window, GlfwKeyCallback);
	glfwSetCursorPosCallback(_window, GlfwCursorPositionCallback);
	glfwSetMouseButtonCallback(_window, GlfwMouseButtonCallback);
}

RanokCADApp* RanokCADApp::Init(const Params& params)
{
	if (!sApplicationSingleton)
		sApplicationSingleton.reset(new RanokCADApp(params));
	
	return sApplicationSingleton.get();
}

RanokCADApp* RanokCADApp::Get()
{
	return sApplicationSingleton.get();
}

RanokCADApp::~RanokCADApp()
{
	bgfx::shutdown();
	glfwTerminate();
}

void RanokCADApp::Run()
{
	constexpr int clearViewId = 0;
	bgfx::setViewClear(clearViewId, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
	bgfx::setViewRect(clearViewId, 0, 0, _params.width, _params.height);

	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
		// const bx::Vec3 at = {0.0f, 0.0f,  0.0f};
		// const bx::Vec3 eye = {0.0f, 0.0f, -5.0f};
		// float view[16];
		// bx::mtxLookAt(view, eye, at);
		// float proj[16];
		// bx::mtxProj(proj, 60.0f, float(_params.width) / float(_params.height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
		// bgfx::setViewTransform(0, view, proj);
		// Handle _window resize.
		int oldWidth = _params.width, oldHeight = _params.height;
		glfwGetWindowSize(_window, &_params.width, &_params.height);
		if (_params.width != oldWidth || _params.height != oldHeight)
		{
			bgfx::reset((uint32_t)_params.width, (uint32_t)_params.height, BGFX_RESET_VSYNC);
			bgfx::setViewRect(clearViewId, 0, 0, bgfx::BackbufferRatio::Equal);
		}
		bgfx::touch(clearViewId);

		Graphics();
		
		bgfx::frame();
	}
}

void RanokCADApp::HandleKeyboard()
{
}

void RanokCADApp::Graphics()
{
}

void RanokCADApp::GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Get()->KeyCallback(key, scancode, action, mods);
}

void RanokCADApp::KeyCallback(int key, int scancode, int action, int mods)
{
}

void RanokCADApp::GlfwCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	Get()->CursorPositionCallback(xpos, ypos);
}

void RanokCADApp::CursorPositionCallback(double xpos, double ypos)
{
}

void RanokCADApp::GlfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Get()->MouseButtonCallback(button, action, mods);
}

void RanokCADApp::MouseButtonCallback(int button, int action, int mods)
{
}



// void RanokCADApp::SetDefaultStyle()
// {
    // auto& style = ImGui::GetStyle();
    // style.WindowPadding = ImVec2(8.00f, 8.00f);
    // style.FramePadding = ImVec2(10.00f, 4.00f);
    // style.CellPadding = ImVec2(6.00f, 6.00f);
    // style.ItemSpacing = ImVec2(6.00f, 6.00f);
    // style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    // style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    // style.IndentSpacing = 25;
    // style.ScrollbarSize = 10;
    // style.GrabMinSize = 10;
    // style.WindowBorderSize = 1;
    // style.ChildBorderSize = 1;
    // style.PopupBorderSize = 1;
    // style.FrameBorderSize = 1;
    // style.TabBorderSize = 1;
    // style.WindowRounding = 7;
    // style.ChildRounding = 4;
    // style.FrameRounding = 3;
    // style.PopupRounding = 4;
    // style.ScrollbarRounding = 9;
    // style.GrabRounding = 3;
    // style.LogSliderDeadzone = 4;
    // style.TabRounding = 4;
    //
    // ImVec4* colors = ImGui::GetStyle().Colors;
    // colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    // colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    // colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    // colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    // colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    // colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    // colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    // colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    // colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    // colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    // colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    // colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    // colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    // colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    // colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    // colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    // colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    // colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    // colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    // colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    // colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    // colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    // colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    // colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    // colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    // colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    // colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    // colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    // colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    // colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    // colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    // colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    // colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    // colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    // colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    // colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    // colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    // colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    // colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    // colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    // colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    // colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    // colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    // colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    // colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    // colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    // colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    // colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    // colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    // colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    // colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    // colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    // colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
    // colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
    // colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.2f);
    //
    // ImGuiIO& io = ImGui::GetIO();
    //
    // std::string fontPath = "Assets/Fonts/Roboto/Roboto-Regular.ttf";
    // ImFont* font1 = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 16, nullptr, io.Fonts->GetGlyphRangesCyrillic());
    // io.FontDefault = font1;
// }
