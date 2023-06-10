#pragma once
#ifdef _WIN32
#include <windows.h>
#else
#include <chrono>
#endif
#include <string>
class Timer
{
private:
	double m_LastTime;
public:
	/// Create a new timer and reset it
	Timer() { Reset(); }

	/// Reset the timer to the current time
	void Reset() ;

	/// Total time since the start of the engine clock in milliseconds
	double TotalTime();

	/// Start recording
	void Record();

	/// Elapsed time since record() in milliseconds
	double Elapsed();
protected:
#ifdef _WIN32
	double m_PCFreq = 0;
	int64_t m_CounterStart = 0;
#else
	std::chrono::time_point<std::chrono::high_resolution_clock> m_CounterStart;
	std::atomic_flag m_Initialized = ATOMIC_FLAG_INIT;
#endif
};