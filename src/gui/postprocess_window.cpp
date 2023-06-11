#include "gui/postprocess_window.h"
#include <imgui/imgui.h>
namespace NerfShot
{
    void PostProcessWindow::OnImGui()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("PostProcess");


		ImGui::End();
		ImGui::PopStyleVar();
    }
}
