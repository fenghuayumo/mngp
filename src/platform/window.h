#pragma once

#include "core/base_type.h"
#include "events/event.h"
#include <functional>
#include "core/math/vec2.h"

namespace NerfShot
{
	struct  WindowProperties
	{
		WindowProperties(uint32 width = 1280, uint32 height = 720,const std::string& title = "SuperD", bool fullscreen = false, bool vSync = true, bool borderless = false, const std::string& filepath = "")
			: Width(width)
			, Height(height)
			, Title(title)
			, Fullscreen(fullscreen)
			, VSync(vSync)
			, Borderless(borderless)
			, FilePath(filepath)
		{
		}

		uint32 Width, Height;
		bool Fullscreen;
		bool VSync;
		bool Borderless;
		bool ShowConsole = true;
		std::string Title;
		std::string FilePath;
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		static std::unique_ptr<Window> Create(const WindowProperties& properties);
		virtual ~Window() = default;
		/// <summary>
		/// CreateGPUDevice and set swapchain
		/// </summary>
		/// <returns></returns>
		bool Initialize();
		bool HasInitialised() const
		{
			return m_Init;
		};
		void    OnResize(int width, int height);
		virtual bool GetExit() const = 0;
		virtual void SetExit(bool exit) = 0;

		inline void SetHasResized(bool resized)
		{
			m_HasResized = resized;
		}
		inline bool GetHasResized() const
		{
			return m_HasResized;
		}
		inline bool GetVsync() const { return m_VSync; }
		inline bool IsFullScreen() const { return m_FullScreen; }
		virtual void ToggleVSync() = 0;
		virtual void SetVSync(bool set) = 0;
		virtual void SetWindowTitle(const std::string& title) = 0;
		virtual void OnUpdate() = 0;
		virtual void SetBorderlessWindow(bool borderless) = 0;
		virtual void* GetHandle()
		{
			return nullptr;
		};
		virtual float GetScreenRatio() const = 0;
		virtual void HideMouse(bool hide) {};
		virtual void SetMousePosition(const int2& pos) {};
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetIcon(const std::string& filePath, const std::string& smallIconFilePath = "") = 0;

		virtual std::string GetTitle() const = 0;
		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;
		//SwapChain&	GetSwapChain() {return m_swapChain;}
		
	protected:

		Window() = default;

		bool m_Init = false;
		int2 m_Position;
		bool m_VSync = false;
		bool m_FullScreen = false;
		bool m_HasResized = false;

		//SwapChain m_swapChain;
	};

}
