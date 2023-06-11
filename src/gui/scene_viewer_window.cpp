#include "scene_viewer_window.h"
#include <imgui.h>
namespace NerfShot
{
    SceneViewerWindow::SceneViewerWindow()
	{
	}
	void SceneViewerWindow::OnImGui()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");


		ImGui::End();
		ImGui::PopStyleVar();
	}
}