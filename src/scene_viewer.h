#pragma once
#include "application.h"
#include "core/log.h"
#include "gui/editor_window.h"

namespace NerfShot
{
	class SceneViewer final : public NerfShot::Application
	{
	public:
		SceneViewer(const std::string& name = "SceneViewer", char** argv = nullptr);
		~SceneViewer()
		{
		}

		void OnImGuiRender();
	public:
		void DrawMenuBar();
		void BeginDockSpace(bool infoBar);
		void EndDockSpace();

	private:
		std::vector<std::shared_ptr<NerfShot::EditorWindow>> m_Windows;

		std::shared_ptr<class InfoPanelWindow>	m_InfoPanel;
	};
}

