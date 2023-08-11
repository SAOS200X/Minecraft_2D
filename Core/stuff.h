#pragma once
#include <chrono>


typedef const char* string;

namespace m_macro{
	const string name_0 = "Minecraft 2D";
	const string name_1 = "RESOLUTION";
	const string name_2 = "FPS";
	const string name_3 = "APPLY";
	const string init_0 = "resource/init/setting.init";
	const string init_1 = "resource/init/window.init";
	const string bg_0 = "resource/image/bg_main.png";
	const string bg_1 = "resource/image/bg_setting.png";
	const string button_0 = "resource/image/blank.png";
	const string button_1 = "resource/image/option.png";
	const string button_2 = "resource/image/quit.png";
	const string button_3 = "resource/image/singleplayer.png";
	const string button_4 = "resource/image/multiplayer.png";
	const string font_0 = "resource/material/font.tff";
}


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


