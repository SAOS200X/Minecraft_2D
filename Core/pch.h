#pragma once

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

#include "SFML/Graphics.hpp"
#include <Windows.h>

#include "s_System.h"

#define logERROR(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12), std::cout << "ERROR" << " -> " << __FUNCTION__ << " -> " << __LINE__ << " -> " << x << "\n"
#define logWARNING(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14), std::cout << "WARNING" << " -> " << __FUNCTION__ << " -> " << __LINE__ << " -> " << x << "\n"
#define logMSG(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10), std::cout << "MSG" << " -> " << __FUNCTION__ << " -> " << __LINE__ << " -> " << x << "\n"

