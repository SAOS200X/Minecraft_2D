#pragma once

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <map>
#include <sstream>

#include <variant>
#include <optional>

#include "SFML/Graphics.hpp"
#include <Windows.h>


#include "stuff.h"



#if 0
#define _MY_DEBUG_ DebugHandle dd(__FUNCTION__);
#else
#define _MY_DEBUG_
#endif

#define logERROR(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12), std::cout << "ERROR" << " -> " << __FUNCTION__ << " -> " << __LINE__ << " -> " << x << "\n"
#define logWARNING(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14), std::cout << "WARNING" << " -> " << __FUNCTION__ << " -> " << __LINE__ << " -> " << x << "\n"
#define logMSG(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15), std::cout << "MSG" << " -> " << __FUNCTION__ << " -> " << __LINE__ << " -> " << x << "\n"

