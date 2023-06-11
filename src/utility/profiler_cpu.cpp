#include "profiler_cpu.h"
#include "engine/engine.h"
#include <xhash>
namespace NerfShot
{
	std::unordered_map<size_t, ProfilerCPU::Event>	ProfilerCPU::m_Events;
	bool		ProfilerCPU::m_Enabled = true;
	size_t		ProfilerCPU::m_FrameEventID = 0;
	std::mutex	ProfilerCPU::m_Lock;

	void ProfilerCPU::BeginFrame()
	{
		m_FrameEventID = BeginEvent("CPU Frame");
	}

	void ProfilerCPU::EndFrame()
	{
		EndEvent(m_FrameEventID);

		for (auto& x : m_Events)
		{
			auto& e = x.second;

			e.Times[e.AvgCounter++ % ARRAY_COUNT(e.Times)] = e.Time;

			if (e.AvgCounter > ARRAY_COUNT(e.Times))
			{
				float avg_time = 0;
				for (int i = 0; i < ARRAY_COUNT(e.Times); ++i)
				{
					avg_time += e.Times[i];
				}
				e.Time = avg_time / ARRAY_COUNT(e.Times);
			}
			if (m_FrameEventID == x.first)
			{
				Engine::Get().FrameStatistics().FrameTime = e.Time;
				Engine::Get().FrameStatistics().FramesPerSecond = 1000.0 / e.Time;
			}
		}
	}

	size_t	ProfilerCPU::BeginEvent(const char* name)
	{
		if (!m_Enabled)
			return 0;

		auto id = std::hash<const char*>()(name);
		
		m_Lock.lock();
		if (m_Events.find(id) == m_Events.end())
		{
			Event e;
			e.Name = name;
			e.Time = 0;
			e.Start.Reset();
			m_Events[id] = e;
		}
		m_Events[id].Start.Record();

		m_Lock.unlock();

		return id;
	}

	void  ProfilerCPU::EndEvent(size_t id)
	{
		if (!m_Enabled)
			return;

		m_Lock.lock();

		auto it = m_Events.find(id);
		if (it != m_Events.end())
		{
			it->second.Time = (float)abs(it->second.Start.Elapsed());
		}
		m_Lock.unlock();
	}

	void ProfilerCPU::SetEnabled(bool value)
	{
		if (value != m_Enabled)
		{
			m_Events.clear();
			m_Enabled = value;
		}
	}
}
