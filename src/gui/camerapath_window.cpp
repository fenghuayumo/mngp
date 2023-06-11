#include "camerapath_window.h"
#include <imgui.h>
namespace NerfShot
{
    CameraPathWindow::CameraPathWindow()
	{
	}
	void CameraPathWindow::OnImGui()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("CameraPath");


		ImGui::End();
		ImGui::PopStyleVar();
	}
}