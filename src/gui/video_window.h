#pragma once

#include "editor_window.h"

namespace NerfShot
{
    class VideoWindow : public EditorWindow
	{
	public:
		VideoWindow();
		~VideoWindow() = default;

	public:
		void	OnImGui() override;
	};
}