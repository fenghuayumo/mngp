#include "application.h"
#include "core/log.h"
#include "platform/input.h"

namespace NerfShot
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name, char** argv)
	{
		//ASSERT(!s_Instance, TEXT("Application already exists!"));
		s_Instance = this;
		Input::Create();

		WindowProperties props;
		// DEFAULT USE VULKAN API
		m_Window = Window::Create(props);
		m_Window->Initialize();
		m_Window->SetEventCallback(NRS_BIND_EVENT_FN(Application::OnEvent));

	}

	Application::~Application()
	{

	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		Input::GetInput()->OnEvent(e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(NRS_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(NRS_BIND_EVENT_FN(Application::OnWindowResize));
	}

	void Application::Run()
	{
		while (m_Running)
		{
			//auto time = Platform::GetTimeSeconds();
			//auto timestep = time - m_LastFrameTime;

			//m_LastFrameTime = time;

			m_Window->OnUpdate();

			if (!m_Minimized)
			{
				Update(0);

				Render();
			}

			if (Input::GetInput()->GetKeyPressed(Key::Escape))
				m_Running = false;

		}
	}

	void Application::Update(const float& timestep)
	{

	}

	void Application::OnImGuiRender()
	{
	}

	void Application::Render()
	{
		static bool showGui = true;
		if (Input::GetInput()->GetKeyPressed(Key::G))
			showGui = !showGui;
	}

	void Application::FixedUpdate()
	{
	}

	void Application::Exit()
	{
		m_Running = false;

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		int width = e.GetWidth(), height = e.GetHeight();

		if (width == 0 || height == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;

		m_Window->OnResize(width, height);

		return true;
	}

	bool Application::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		return true;
	}

	bool Application::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		return true;
	}

}

