#include "video_window.h"
#include <imgui.h>
namespace NerfShot
{
    VideoWindow::VideoWindow()
	{
	}
	void VideoWindow::OnImGui()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Video");


		ImGui::End();
		ImGui::PopStyleVar();
	}
}