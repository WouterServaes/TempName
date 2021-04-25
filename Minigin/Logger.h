#pragma once
#include <ctime>
class Logger
{
public:

	static void LogInfo(const char* msg, const bool timeStamp = true)
	{
		LogMsg(Level::Info, msg, timeStamp);
	}

	static void LogWarning(const char* msg, const  bool timeStamp = true)
	{
		LogMsg(Level::Warning, msg, timeStamp);
	}

	static void LogError(const char* msg, const  bool timeStamp = true)
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
	enum class Level { Info, Warning, Error };
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
	}

	
};
