
#include "window.h"
 #include "platform/glfw_window.h"
// #include "Platform/Windows/Win32Window.h"
// #include "Graphics/Graphics.h"

namespace NerfShot
{
	std::unique_ptr<Window> Window::Create(const WindowProperties& properties)
	{
		std::unique_ptr<Window>	window;
		window = GLFWWindow::CreateFuncGLFW(properties);
		return window;
	}
	bool Window::Initialize()
	{
		// auto device = CreateGpuDevice(Graphics::GetGraphicsAPI());
		// SwapChainDesc desc;
		// desc.width = GetWidth();
		// desc.height = GetHeight();
		// desc.buffercount = 3;
		// desc.format = FORMAT_R10G10B10A2_UNORM;
		// desc.vsync = false;
		// device->CreateSwapChain(&desc, this, &m_swapChain);
		return true;
	}

	void Window::OnResize(int width, int height)
	{
		// auto device = GpuDevice::Instance.get();
		// SwapChainDesc desc;
		// desc.width = GetWidth();
		// desc.height = GetHeight();
		// desc.buffercount = 3;
		// desc.format = FORMAT_R10G10B10A2_UNORM;
		// desc.vsync = false;
		// device->CreateSwapChain(&desc, this, &m_swapChain);
	}

}
