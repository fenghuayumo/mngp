#pragma once
#include "editor_window.h"

namespace NerfShot
{
    class InfoPanelWindow : public EditorWindow
    {
	public:
		void	OnImGui() override;
    };
}
