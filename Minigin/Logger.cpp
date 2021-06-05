#include "MiniginPCH.h"
#include "Logger.h"

void Logger::ThrowErrorBox(const std::string& message)
{
	//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
#if _DEBUG
	const auto msgBoxmsg{ (message + static_cast<std::string>("\n\n Try again: puts breakpoint in program\n Continue: continues program (may result in more crashes)\nCancel: closes program (beware leaks)")) };

	const auto msgBoxReturn{ MessageBoxA(0, msgBoxmsg.c_str(), "[ERROR]", MB_ICONERROR | MB_CANCELTRYCONTINUE | MB_TOPMOST | MB_DEFBUTTON2) };
	if (msgBoxReturn == IDTRYAGAIN)
	{
		// is there a way to step through the call stack through code? breakpoint gets put here, but the user should see the actual error.
		//
		__debugbreak();
	}
	else if (msgBoxReturn == IDCANCEL)
		exit(-1);
#else

	const auto msgBoxmsg{ (static_cast<std::string>("Critical error:\n") + msg + static_cast<std::string>("\n\n Click OK to close program")) };

	const auto msgBoxReturn{ MessageBoxA(0, msgBoxmsg.c_str(), "[ERROR]", MB_ICONERROR | MB_OK | MB_TOPMOST) };
	if (msgBoxReturn == IDOK)
	{
		exit(-1);
	}
#endif
}
