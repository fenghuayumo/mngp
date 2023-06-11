
#if defined(NRS_PLATFORM_MACOS)
#	define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include "core/log.h"
#include "glfw_window.h"
//// #include "Loader/ImageLoader.h"
#include "platform/glfw_key_codes.h"

#include "platform/input.h"
#include "events/application_event.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <imgui/imgui.h>
//static GLFWcursor* g_MouseCursors[ImGuiMouseCursor_COUNT] = {0};
#define NRS_RENDER_API_OPENGL 1

namespace NerfShot
{
	static bool s_GLFWInitialized = false;
	static int s_NumGLFWWindows = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		NRS_CORE_ERROR("GLFW Error - {0} : {1}", error, description);
	}

	GLFWWindow::GLFWWindow(const WindowProperties& properties)
	{
		m_Init = false;
		m_VSync = properties.VSync;
		m_HasResized = true;
		m_Init = Init(properties);
		
	}

	GLFWWindow::~GLFWWindow()
	{
	/*	for(ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_COUNT; cursor_n++)
		{
			glfwDestroyCursor(g_MouseCursors[cursor_n]);
			g_MouseCursors[cursor_n] = NULL;
		}*/

		glfwDestroyWindow(m_Handle);
       
       
		s_NumGLFWWindows--;

		if(s_NumGLFWWindows < 1)
		{
			s_GLFWInitialized = false;
			glfwTerminate();
		}
	}

	bool GLFWWindow::Init(const WindowProperties& properties)
	{
		NRS_CORE_INFO("Creating window - Title : {0}, Width : {1}, Height : {2}", properties.Title, properties.Width, properties.Height);

		if(!s_GLFWInitialized)
		{
			int success = glfwInit();
			// static_assert(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		s_NumGLFWWindows++;

#ifdef NRS_RENDER_API_OPENGL
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#	ifdef NRS_PLATFORM_MACOS
			glfwWindowHint(GLFW_SAMPLES, 1);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
			glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
			glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, GL_TRUE);
			glfwWindowHint(GLFW_STENCIL_BITS, 8); // Fixes 16 bit stencil bits in macOS.
			glfwWindowHint(GLFW_STEREO, GLFW_FALSE);
			glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
#	endif
		}
#endif

		SetBorderlessWindow(properties.Borderless);

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		uint32 ScreenWidth = 0;
		uint32 ScreenHeight = 0;

		if(properties.Fullscreen)
		{
			ScreenWidth = mode->width;
			ScreenHeight = mode->height;
		}
		else
		{
			ScreenWidth = properties.Width;
			ScreenHeight = properties.Height;
		}

		m_Data.Title = properties.Title;
		m_Data.Width = ScreenWidth;
		m_Data.Height = ScreenHeight;
		m_Data.Exit = false;

#ifdef NRS_RENDER_API_VULKAN
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

		m_Handle = glfwCreateWindow(ScreenWidth, ScreenHeight, properties.Title.c_str(), nullptr, nullptr);


		glfwMakeContextCurrent(m_Handle);

		glfwSetWindowUserPointer(m_Handle, &m_Data);

#ifdef NRS_PLATFORM_WINDOWS
		//SetIcon("/Textures/icon.png", "/Textures/icon32.png");
#endif

		glfwSetWindowPos(m_Handle, mode->width / 2 - ScreenWidth / 2, mode->height / 2 - ScreenHeight / 2);
		glfwSetInputMode(m_Handle, GLFW_STICKY_KEYS, true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *static_cast<WindowData*>((glfwGetWindowUserPointer(window)));

			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window) {
			WindowData& data = *static_cast<WindowData*>((glfwGetWindowUserPointer(window)));
			WindowCloseEvent event;
			data.EventCallback(event);
			data.Exit = true;
		});

		glfwSetWindowFocusCallback(m_Handle, [](GLFWwindow* window, int focused) {
			Input::GetInput()->SetWindowFocus(focused);
		});
		glfwSetWindowIconifyCallback(m_Handle, [](GLFWwindow* window, int32_t state)
			{
				switch (state)
				{
				case 1:
					Input::GetInput()->SetWindowFocus(false);
					break;
				case 0:
					Input::GetInput()->SetWindowFocus(true);
					break;
				default:
					NRS_ERROR("Unsupported window iconify state from callback");
				}
			});


		glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *static_cast<WindowData*>((glfwGetWindowUserPointer(window)));

			switch(action)
			{
			case GLFW_PRESS: {
				KeyPressedEvent event(GLFWKeyCodes::GLFWToNeoxRayKeyboardKey(key), 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(GLFWKeyCodes::GLFWToNeoxRayKeyboardKey(key));
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(GLFWKeyCodes::GLFWToNeoxRayKeyboardKey(key), 1);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *static_cast<WindowData*>((glfwGetWindowUserPointer(window)));

			switch(action)
			{
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(GLFWKeyCodes::GLFWToLumosMouseKey(button));
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(GLFWKeyCodes::GLFWToLumosMouseKey(button));
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *static_cast<WindowData*>((glfwGetWindowUserPointer(window)));

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *static_cast<WindowData*>((glfwGetWindowUserPointer(window)));

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

		glfwSetCursorEnterCallback(m_Handle, [](GLFWwindow* window, int enter) {
			WindowData& data = *static_cast<WindowData*>((glfwGetWindowUserPointer(window)));

			MouseEnterEvent event(enter > 0);
			data.EventCallback(event);
		});

		glfwSetCharCallback(m_Handle, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *static_cast<WindowData*>((glfwGetWindowUserPointer(window)));

			KeyTypedEvent event(GLFWKeyCodes::GLFWToNeoxRayKeyboardKey(keycode), char(keycode));
			data.EventCallback(event);
		});

		//g_MouseCursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		//g_MouseCursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		//g_MouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		//g_MouseCursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		//g_MouseCursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		//g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		//g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		//g_MouseCursors[ImGuiMouseCursor_Hand] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

		NRS_CORE_INFO("Initialised GLFW version : {0}", glfwGetVersionString());

		return true;
	}

	void GLFWWindow::SetIcon(const std::string& filePath, const std::string& smallIconFilePath)
	{
	/*	uint32 width, height;
		std::vector<GLFWimage> images;
		if (filePath != "")
		{
			uint32 width, height;
			uint8* pixels = ImageIO::LoadImageFromFile(filePath, &width, &height, nullptr, nullptr, true);

			GLFWimage image;
			image.height = height;
			image.width = width;
			image.pixels = static_cast<unsigned char*>(pixels);
			images.push_back(image);
		}

		if (smallIconFilePath != "")
		{
			uint32 width, height;
			uint8* pixels = ImageIO::LoadImageFromFile(smallIconFilePath, &width, &height, nullptr, nullptr, true);
			GLFWimage image;
			image.height = height;
			image.width = width;
			image.pixels = static_cast<unsigned char*>(pixels);
			images.push_back(image);
		}


		glfwSetWindowIcon(m_Handle, int(images.size()), images.data());

		for (auto imag : images)
		{
			delete[] imag.pixels;
		}*/
	}

	void GLFWWindow::SetWindowTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_Handle, title.c_str());
	}

	void GLFWWindow::ToggleVSync()
	{
		if(m_VSync)
		{
			SetVSync(false);
		}
		else
		{
			SetVSync(true);
		}
	}

	void GLFWWindow::SetVSync(bool set)
	{
		if(set)
		{
			m_VSync = true;
			glfwSwapInterval(1);
		}
		else
		{
			m_VSync = false;
			glfwSwapInterval(0);
		}
	}

	void GLFWWindow::OnUpdate()
	{
		glfwSwapBuffers(m_Handle);


		glfwPollEvents();
	}

	void GLFWWindow::SetBorderlessWindow(bool borderless)
	{
		if(borderless)
		{
			glfwWindowHint(GLFW_DECORATED, false);
		}
		else
		{
			glfwWindowHint(GLFW_DECORATED, true);
		}
	}

	void GLFWWindow::HideMouse(bool hide)
	{
		if(hide)
		{
			glfwSetInputMode(m_Handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else
		{
			glfwSetInputMode(m_Handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	void GLFWWindow::SetMousePosition(const int2& pos)
	{
		glfwSetCursorPos(m_Handle, pos.x, pos.y);
	}

	std::unique_ptr<Window> GLFWWindow::CreateFuncGLFW(const WindowProperties& properties)
	{
		return std::make_unique<GLFWWindow>(properties);
	}
}
