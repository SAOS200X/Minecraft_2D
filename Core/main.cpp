#include "pch.h"
#include "Core.h"

#ifndef _DEBUG
#define dllprocess __declspec(dllexport)
#else
#define dllprocess
#endif // _DEBUG

dllprocess void start()
{
	Core c;
	c.run();	
}