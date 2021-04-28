#pragma once
#include "time.h"
class Logger
{
public:

	static void LogInfo(const char* msg, const bool timeStamp = true)
	{
		LogMsg(Level::Info, msg, timeStamp);
	}

	static void LogWarning(const char* msg, const bool timeStamp = true)
	{
		LogMsg(Level::Warning, msg, timeStamp);
	}

	static void LogError(const char* msg, const bool timeStamp = true)
	{
		LogMsg(Level::Error, msg, timeStamp);
	}

	~Logger() = default;
	Logger() = delete;
	Logger(const Logger& other) = delete;
	Logger(Logger&& other) = delete;
	Logger& operator=(const Logger& other) = delete;
	Logger& operator=(Logger&& other) = delete;
private:

	enum class Level
	{
		Info,
		Warning,
		Error
	};

	static void LogMsg(const Level level, const char* msg, const bool timeStamp = true)
	{
		const char* prefix{};
		switch (level)
		{
		case Level::Info:
			prefix = " [INFO]\t";
			break;
		case Level::Warning:
			prefix = " [WARNING]\t";
			break;
		case Level::Error:
			prefix = " [ERROR]\t";
			break;
		default:
			break;
		}

		if (timeStamp)
		{
			SYSTEMTIME time;
			GetSystemTime(&time);
			std::string timeStr{};
			if (time.wHour < 10) timeStr += "0";
			timeStr += std::to_string(time.wHour) + ":";
			if (time.wMinute < 10) timeStr += "0";
			timeStr += std::to_string(time.wMinute) + ":";
			if (time.wSecond < 10) timeStr += "0";
			timeStr += std::to_string(time.wSecond);
			std::cout << timeStr;
		}

		std::cout << prefix << msg << std::endl;

		if (level == Level::Error)
		{
			//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
#if _DEBUG
			const auto msgBoxmsg{ (msg + static_cast<std::string>("\n\n Try again: puts breakpoint in program\n Continue: continues program (may result in more crashes)\nCancel: closes program (beware leaks)")) };

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
	}
};
