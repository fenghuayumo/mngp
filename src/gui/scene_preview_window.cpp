#include "scene_preview_window.h"
#include <imgui.h>
namespace NerfShot
{
	void ScenePreviewWindow::OnImGui()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("PreView");


		ImGui::End();
		ImGui::PopStyleVar();
	}
}