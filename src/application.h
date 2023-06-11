#pragma once
#include <string>
#include "platform/window.h"
#include "platform/events/application_event.h"
#include "platform/events/key_event.h"
#include "platform/events/mouse_event.h"

namespace NerfShot
{
	class Application
	{
	public:
		Application(const std::string& name = "NerFShot App", char** argv = nullptr);
		virtual ~Application();

		void OnEvent(Event& e);

		Window& GetWindow() { return *m_Window; }

		void Close();

		static Application& Get() { return *s_Instance; }

		virtual	void Run();
		virtual void Update(const float& step);
		virtual void Render();
		virtual	void OnImGuiRender();
		void		 Exit();
		void		 FixedUpdate();
		virtual bool OnWindowClose(WindowCloseEvent& e);
		virtual bool OnWindowResize(WindowResizeEvent& e);
		virtual bool OnKeyPressedEvent(KeyPressedEvent& e);
		virtual	bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		static Application* s_Instance;

		std::unique_ptr<class EditGui> m_edit_gui;
	protected:
	public:

	protected:
	};

	// To be defined in CLIENT
	Application* CreateApplication(char** argv);
}
