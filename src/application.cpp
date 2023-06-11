#include "application.h"
#include "core/log.h"
#include "platform/input.h"
#include "engine/engine.h"
#include "utility/profiler_cpu.h"
#include "gui/gui.h"
#include "graphics/gpu_context.h"
#include "graphics/gpu_device.h"
#include <iostream>
namespace NerfShot
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name, char** argv)
	{
		//ASSERT(!s_Instance, TEXT("Application already exists!"));
		s_Instance = this;
		Input::Create();

		WindowProperties props;
		props.Title = name;
		// DEFAULT USE VULKAN API
		m_Window = Window::Create(props);
		m_Window->Initialize();
		m_Window->SetEventCallback(NRS_BIND_EVENT_FN(Application::OnEvent));


		GpuDevice::Get().initialize();
		m_edit_gui = std::make_unique<EditGui>();
		m_edit_gui->init(m_Window.get());
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
			Timer timer;
			if (!m_Minimized)
			{
				Update(0);

				Render();
			}
			//std::cout << "FPS: " << 1000.0f / timer.Elapsed() << std::endl;

			if (Input::GetInput()->GetKeyPressed(Key::Escape))
				m_Running = false;
			m_Window->OnUpdate();
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
		ProfilerCPU::BeginFrame();
		static bool showGui = true;
		if (Input::GetInput()->GetKeyPressed(Key::G))
			showGui = !showGui;

		GpuDevice::Get().get_main_context()->begin_frame(m_Window.get());
		if (showGui)
		{
			m_edit_gui->begin();

			OnImGuiRender();

			m_edit_gui->end();
		}

		GpuDevice::Get().get_main_context()->end_frame(m_Window.get());
		Engine::Get().FrameStatistics().FrameCount++;

		//std::cout << "FPS: " << Engine::Get().FrameStatistics().FramesPerSecond << std::endl;
		ProfilerCPU::EndFrame();
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
		m_edit_gui->shut_down();
		GpuDevice::Get().destroy();
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

