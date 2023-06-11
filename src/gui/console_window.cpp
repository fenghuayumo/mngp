#include "console_window.h"
#include <imgui.h>
namespace NerfShot
{
    ConsoleWindow::ConsoleWindow()
	{
	}
	void ConsoleWindow::OnImGui()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Console");


		ImGui::End();
		ImGui::PopStyleVar();
	}
}