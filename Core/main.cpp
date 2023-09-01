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



//	DONE Use Define value and filename incode  
//	DONE Add more config and Apperant         
//		work with Game State   
//  DONE menu when esc and save game             
//		create player class
//			Work with game physics
//  DONE	create tiles map
//			Enhance Tile Map generation
//      some game mechanism
//		Fix Game FPS and CPU
