#include "Timer.h"
#include <iostream>

void Timer::Reset()
{
#ifdef _WIN32
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	m_PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	m_CounterStart = li.QuadPart;
#else
	m_CounterStart = std::chrono::high_resolution_clock::now();
#endif // _WIN32
}

double Timer::TotalTime()
{
#ifdef _WIN32
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - m_CounterStart) / m_PCFreq;
#else
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_seconds = now - m_CounterStart;
	return elapsed_seconds.count();
#endif // _WIN32
}

void Timer::Record()
{
	m_LastTime = TotalTime();
}
double Timer::Elapsed()
{
	return TotalTime() - m_LastTime;
}