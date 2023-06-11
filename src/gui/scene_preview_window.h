#pragma once
#include "editor_window.h"

namespace NerfShot
{
    class ScenePreviewWindow : public EditorWindow
    {
	public:
		void	OnImGui() override;
    };
}