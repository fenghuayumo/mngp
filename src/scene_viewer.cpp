#include "scene_viewer.h"
#include "gui/postprocess_window.h"
#include "gui/camerapath_window.h"
#include "gui/scene_preview_window.h"
#include "gui/scene_viewer_window.h"
#include "gui/console_window.h"
#include "gui/camerapath_window.h"
#include "gui/video_window.h"

#include "gui/Info_window.h"
#include <imgui/imgui.h>
namespace NerfShot
{
	SceneViewer::SceneViewer(const std::string& name, char** argv)
		:NerfShot::Application(name, argv)
	{
		m_InfoPanel = std::make_shared<InfoPanelWindow>();
		m_Windows.push_back(std::make_shared<PostProcessWindow>());
		m_Windows.push_back(std::make_shared<SceneViewerWindow>());
		m_Windows.push_back(std::make_shared<ConsoleWindow>());
		m_Windows.push_back(std::make_shared<CameraPathWindow>());
		m_Windows.push_back(std::make_shared<VideoWindow>());
		m_Windows.push_back(std::make_shared<ScenePreviewWindow>());
		for (auto w : m_Windows)
			w->SetApplication(this);
		m_InfoPanel->SetApplication(this);

	}


	void  SceneViewer::OnImGuiRender()
	{
		BeginDockSpace(false);

		for (auto& window : m_Windows)
		{
			if (window->Active())
				window->OnImGui();
		}
		if (m_InfoPanel->Active())
			m_InfoPanel->OnImGui();
		DrawMenuBar();
		EndDockSpace();
	}

	void SceneViewer::DrawMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
			}
		}
	}

	void SceneViewer::BeginDockSpace(bool infoBar)
	{
		static bool p_open = true;
		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();

			auto pos = viewport->Pos;
			auto size = viewport->Size;
			bool menuBar = true;
			if (menuBar)
			{
				const float infoBarSize = 19.0f;
				pos.y += infoBarSize;
				size.y -= infoBarSize;
			}

			if (infoBar)
			{
				const float infoBarSize = 24.0f;
				pos.y += infoBarSize;
				size.y -= infoBarSize;
			}

			ImGui::SetNextWindowPos(pos);
			ImGui::SetNextWindowSize(size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the
		// pass-thru hole, so we ask Begin() to not render a background.
		//if (opt_flags & ImGuiDockNodeFlags_DockSpace)
		//	window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("MyDockspace", &p_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiID DockspaceID = ImGui::GetID("MyDockspace");

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 100.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGui::DockSpace(DockspaceID, ImVec2(0.0f, 0.0f), opt_flags);
		}

		style.WindowMinSize.x = minWinSizeX;

	}

	void SceneViewer::EndDockSpace()
	{
		ImGui::End();
	}
}

NerfShot::Application* NerfShot::CreateApplication(char** argv)
{
	return new NerfShot::SceneViewer("nerf_viewer", argv);
}
