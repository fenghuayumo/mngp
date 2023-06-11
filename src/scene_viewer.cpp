#include "scene_viewer.h"
#include "gui/postprocess_window.h"
#include "gui/camerapath_window.h"
#include "gui/Info_window.h"

namespace NerfShot
{
	SceneViewer::SceneViewer(const std::string& name, char** argv)
		:NerfShot::Application(name, argv)
	{
		m_InfoPanel = std::make_shared<InfoPanelWindow>();
		m_Windows.push_back(std::make_shared<PostProcessWindow>());
		for (auto w : m_Windows)
			w->SetApplication(this);
		m_InfoPanel->SetApplication(this);

	}


	void  SceneViewer::OnImGuiRender()
	{
		//BeginDockSpace(false);

		for (auto& window : m_Windows)
		{
			if (window->Active())
				window->OnImGui();
		}
		if (m_InfoPanel->Active())
			m_InfoPanel->OnImGui();
		//DrawMenuBar();
		//EndDockSpace();
	}
}

NerfShot::Application* NerfShot::CreateApplication(char** argv)
{
	return new NerfShot::SceneViewer("nerf_viewer", argv);
}
