#pragma once

#include "editor_window.h"

namespace NerfShot
{
    class ConsoleWindow : public EditorWindow
	{
	public:
		ConsoleWindow();
		~ConsoleWindow() = default;

	public:
		void	OnImGui() override;
	};
}