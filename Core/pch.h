#pragma once

#include <iostream>
#include <fstream>

#include "SFML/Graphics.hpp"
#include <Windows.h>

#include "s_System.h"

#ifndef _DEBUG
#define dllprocess __declspec(dllexport)
#else
#define dllprocess
#endif // _DEBUG

#define logMSG(x) std::cout << "ERROR: " << x << " -> " << __FUNCTION__ << " -> " << __LINE__ << "\n"
