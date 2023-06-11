#pragma once

#include "editor_window.h"

namespace NerfShot
{
    class CameraPathWindow : public EditorWindow
	{
	public:
		CameraPathWindow();
		~CameraPathWindow() = default;

	public:
		void	OnImGui() override;
	};
}