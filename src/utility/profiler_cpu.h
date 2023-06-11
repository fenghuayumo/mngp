#pragma once
#include "core/base_type.h"
#include <mutex>
#include <unordered_map>
#include "timer.h"
namespace NerfShot
{
	class  ProfilerCPU
	{
	public:
		struct Event
		{
			const char* Name;

			/// <summary>
		   /// The start time (in milliseconds).
		   /// </summary>
			Timer Start;

			///
			double Time;

			int	   AvgCounter = 0;

			double Times[20];
		};


		static void		BeginFrame();
		static void		EndFrame();
		static size_t	BeginEvent(const char* name);

		static void		EndEvent(size_t index);

		static const std::unordered_map<size_t, Event>& GetLastFrameData() { return m_Events; }

		static	void	SetEnabled(bool valued);
		static	bool	IsEnabled() { return m_Enabled; }
	protected:
		static bool		m_Enabled;
		static std::unordered_map<size_t, Event> m_Events;
		static std::mutex		m_Lock;
		static Timer			m_Timer;
		static size_t			m_FrameEventID;
	};

	/// <summary>
	/// Helper structure used to call BeginEvent/EndEvent within single code block.
	/// </summary>
	struct ScopeProfileBlockCPU
	{
		/// <summary>
		/// The event token index.
		/// </summary>
		size_t Index;

		/// <summary>
		/// Initializes a new instance of the <see cref="ScopeProfileBlockCPU"/> struct.
		/// </summary>
		/// <param name="name">The event name.</param>
		ScopeProfileBlockCPU(const char* name)
		{
			Index = ProfilerCPU::BeginEvent(name);
		}

		/// <summary>
		/// Finalizes an instance of the <see cref="ScopeProfileBlockCPU"/> class.
		/// </summary>
		~ScopeProfileBlockCPU()
		{
			ProfilerCPU::EndEvent(Index);
		}
	};

#define PROFILE_CPU_NAMED(name) ScopeProfileBlockCPU ProfileBlockCPU(name)

#define PROFILE_CPU()  ScopeProfileBlockCPU ProfileBlockCPU(__FUNCTION__)

}
