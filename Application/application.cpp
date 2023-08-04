#ifndef _DEBUG
#define dllprocess __declspec(dllimport)
#else
#define dllprocess
#endif // _DEBUG



dllprocess void start();


void main()
{
	start();
}