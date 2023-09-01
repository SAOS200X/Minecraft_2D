#pragma once
#include <chrono>


typedef const char* string;

namespace m_path {
	const string path_setting = "resource/init/setting.init";
	const string path_window = "resource/init/window.init";
	const string save_global = "resource/saves/global.save";
	const string bg_main = "resource/image/bg_main.png";
	const string bg_setting = "resource/image/bg_setting.png";
	const string bg_singleplayer = "resource/image/bg_singleplayer.png";
	const string bg_newworld = "resource/image/bg_newWorld.png";
	const string button_blank = "resource/image/blank.png";
	const string button_option = "resource/image/option.png";
	const string button_quit = "resource/image/quit.png";
	const string button_singleplayer = "resource/image/singleplayer.png";
	const string font_0 = "resource/material/font.ttf";
	const string font_1 = "resource/material/MC_regular.otf";
	const string tilesheet = "resource/material/tile_sheet.png";
	const string itemsheet = "resource/material/item_sheet.png";
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

class Date
{
public:
	time_t tick;
	tm date;
	//tm* data;

	Date(time_t tick) : tick(tick) { localtime_s(&date, &tick); };

	void reset() { tick = time(0); }
	tm* getDate() { return &date; }
};

template<typename C, typename...T>
C getMin(T...args)
{
	C c = args;
	((args < c ? c = args : c = c),...);

	return c;
}

template<typename T, typename A, typename B>
inline sf::Vector2<T>&& Vector2(const A& a, const B& b) { return std::move(sf::Vector2<T>(static_cast<T>(a), static_cast<T>(b))); }

template<typename T, typename ty>
inline sf::Vector2<T>&& Vector2(const ty& arg) { return std::move(sf::Vector2<T>(static_cast<T>(arg), static_cast<T>(arg))); }

template<typename T>
inline bool operator<(const sf::Vector2<T>& left, const sf::Vector2<T>& right) { return (left.x < right.x); }

template<typename L, typename R>
inline sf::Vector2<L> operator-(const sf::Vector2<L>& left, const sf::Vector2<R>& right) { sf::Vector2<L>(left.x - right.x, left.y - right.y); }

template<typename L, typename R>
inline sf::Vector2<L> operator+(const sf::Vector2<L>& left, const sf::Vector2<R>& right) { sf::Vector2<L>(left.x + right.x, left.y + right.y); }

template<typename L, typename R>
inline sf::Vector2<L> operator*(const sf::Vector2<L>& left, const R& right) { return sf::Vector2<L>(left.x * right, left.y * right); }

template<typename L, typename R>
inline sf::Vector2<R> operator*(const R& right, const sf::Vector2<L>& left) { return sf::Vector2<R>(left.x * right, left.y * right); }

template<typename L, typename R>
inline sf::Vector2<L> operator/(const sf::Vector2<L>& left, const R& right) { return sf::Vector2<L>(left.x / static_cast<L>(right), left.y / static_cast<L>(right)); }
