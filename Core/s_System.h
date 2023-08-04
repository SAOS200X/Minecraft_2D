#pragma once
class s_System
{
public:
	enum state {release, pressed, hold};
	static std::map<unsigned short, s_System::state> KeyState;
	static std::map<unsigned short, s_System::state> MouseState;

};

