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



// Use Define value and filename incode
// Add more config and Apperant
// work with Game State
// create player class
// create tiles map
// some game mechanism
