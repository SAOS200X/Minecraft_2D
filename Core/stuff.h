#pragma once
#include <chrono>

template<typename ty = std::chrono::microseconds>
class Timer
{
public:
	Timer() = default;

	inline long long getEslapseTime() { return std::chrono::duration_cast<ty>(getTime() - currenttick).count(); }

	inline void restart() { this->currenttick = getTime(); }

	inline void log() { printf("%lli\n", std::chrono::duration_cast<ty>(getTime() - currenttick).count()); restart(); }

	inline std::chrono::steady_clock::duration getTime() { return std::chrono::high_resolution_clock::now().time_since_epoch(); }
private:
	std::chrono::steady_clock::duration begin = getTime();
	std::chrono::steady_clock::duration currenttick = begin;
};

struct DebugHandle
{
	Timer< std::chrono::microseconds> t;
	const char* func;

	DebugHandle(const char* s) : func(s) {};
	~DebugHandle() { printf("%s -> %lli\n", func, t.getEslapseTime()); }
};


