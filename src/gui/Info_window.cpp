#include "Info_window.h"

#include "utility/profiler_cpu.h"
#include "engine/engine.h"
#include <imgui.h>
#include <sstream>
#pragma once

namespace NerfShot
{
    void InfoPanelWindow::OnImGui()
    {
		ImGui::Begin("InfoPanel");

		const auto& ProfileCPUDatas = ProfilerCPU::GetLastFrameData();
		for (auto& x : ProfileCPUDatas)
		{
			std::stringstream ss("");
			ss.precision(4);

			ss << x.second.Name << ": " << std::fixed << x.second.Time << "ms" << std::endl;
			ImGui::Text(ss.str().c_str());
		}
		{
			std::stringstream ss("");
			ss.precision(4);
			ss << "FPS: " << Engine::Get().FrameStatistics().FramesPerSecond << std::endl;
			ImGui::Text(ss.str().c_str());
		}

		ImGui::End();
    }
}
