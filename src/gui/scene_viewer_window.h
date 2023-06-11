#pragma once
#include "editor_window.h"

namespace NerfShot
{
    class SceneViewerWindow : public EditorWindow
	{
	public:
		SceneViewerWindow();
		~SceneViewerWindow() = default;

	public:
		void	OnImGui() override;
	};
}