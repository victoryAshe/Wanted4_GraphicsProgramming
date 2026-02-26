#include "Core/Engine.h"

// Graphics Programming.
// Create Window, => Draw images on the window using API.
// Using Win32 API

using namespace Craft;


// Run Engine Function.
void LaunchEngineStartup(HINSTANCE instance)
{
	Engine engine;
	engine.Initialize(instance);
	engine.Run();
}

int main()
{
	LaunchEngineStartup(GetModuleHandle(nullptr));
}


//int WINAPI WinMain(
//	_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPSTR lpCmdLine,
//	_In_ int nShowCmd)
//{
//	LaunchEngineStartup(hInstance);
//
//	return 0;
//}