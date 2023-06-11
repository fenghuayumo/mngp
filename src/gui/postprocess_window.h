#pragma once
#include "editor_window.h"
namespace NerfShot
{
    class PostProcessWindow : public EditorWindow
    {
	public:
		void	OnImGui() override;
    };
}