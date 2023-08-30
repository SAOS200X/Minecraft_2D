#ifndef _DEBUG
#define MAIN_API WinMain()
#define dllprocess __declspec(dllimport)
#else
#define MAIN_API main()
#define dllprocess
#endif // _DEBUG



dllprocess void start();


int MAIN_API
{
	start();
}