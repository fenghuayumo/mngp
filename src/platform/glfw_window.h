#pragma once
#include "platform/window.h"

struct GLFWwindow;
namespace NerfShot
{
	class GLFWWindow : public Window
	{
	public:
		GLFWWindow(const WindowProperties& properties);
		~GLFWWindow();

		void ToggleVSync() override;
		void SetVSync(bool set) override;
		void SetWindowTitle(const std::string& title) override;
		void SetBorderlessWindow(bool borderless) override;
		void OnUpdate() override;
		void HideMouse(bool hide) override;
		void SetMousePosition(const int2& pos) override;

		bool Init(const WindowProperties& properties);

		inline void* GetHandle() override
		{
			return m_Handle;
		}

		inline std::string GetTitle() const override
		{
			return m_Data.Title;
		}
		inline uint32 GetWidth() const override
		{
			return m_Data.Width;
		}
		inline uint32 GetHeight() const override
		{
			return m_Data.Height;
		}
		inline float GetScreenRatio() const override
		{
			return (float)m_Data.Width / (float)m_Data.Height;
		}
		inline bool GetExit() const override
		{
			return m_Data.Exit;
		}
		inline void SetExit(bool exit) override
		{
			m_Data.Exit = exit;
		}
		inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}

		void SetIcon(const std::string& file, const std::string& smallIconFilePath = "") override;
		static std::unique_ptr<Window> CreateFuncGLFW(const WindowProperties& properties);
	protected:
		GLFWwindow* m_Handle;

		struct WindowData
		{
			std::string Title;
			uint32 Width, Height;
			bool VSync;
			bool Exit;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
