#pragma once
#include "utility/singleton.h"
namespace NerfShot
{
	class  Engine : public ThreadSafeSingleton<Engine>
	{
		friend class TSingleton<Engine>;

	public:
		Engine() : m_MaxFramesPerSecond(1000.0f / 60.0f)
		{}
		~Engine()
		{}

		float TargetFrameRate() const { return m_MaxFramesPerSecond; }
		void SetTargetFrameRate(float targetFPS) { m_MaxFramesPerSecond = targetFPS; }

		//static Timestep& GetTimeStep() { return Engine::Get().m_TimeStep; }

		struct FrameStats
		{
			uint32_t	UpdatesPerSecond;
			uint32_t	FramesPerSecond;
			float		FrameTime = 0.1f;
			uint32		FrameCount = 0;
		};

		FrameStats& FrameStatistics() { return m_Stats; }

	private:

		FrameStats m_Stats;
		float m_MaxFramesPerSecond;
	};
}
