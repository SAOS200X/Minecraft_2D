#pragma once
#include <chrono>


typedef const char* string;

namespace m_macro {
	const string path_setting = "resource/init/setting.init";
	const string path_window = "resource/init/window.init";
	const string bg_main = "resource/image/bg_main.png";
	const string bg_setting = "resource/image/bg_setting.png";
	const string bg_singleplayer = "resource/image/bg_singleplayer.png";
	const string button_blank = "resource/image/blank.png";
	const string button_option = "resource/image/option.png";
	const string button_quit = "resource/image/quit.png";
	const string button_singleplayer = "resource/image/singleplayer.png";
	const string button_multiplayer = "resource/image/multiplayer.png";
	const string font_0 = "resource/material/font.ttf";
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


