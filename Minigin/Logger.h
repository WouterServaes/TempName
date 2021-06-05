#pragma once
class Logger
{
public:

	/// <summary>
	/// Prints info in the console
	/// </summary>
	/// <param name="msg">the message</param>
	/// <param name="timeStamp">true: time gets printed before the message</param>
	static void LogInfo(const char* msg, const bool timeStamp = true)
	{
		LogMsg(Level::Info, msg, timeStamp);
	}

	/// <summary>
	/// Prints info in the console
	/// </summary>
	/// <param name="msg">the message</param>
	/// <param name="timeStamp">true: time gets printed before the message</param>
	static void LogInfo(const std::string& msg, const bool timeStamp = true)
	{
		LogMsg(Level::Info, msg.c_str(), timeStamp);
	}

	/// <summary>
	/// Prints a warning in the console
	/// </summary>
	/// <param name="msg">the message</param>
	/// <param name="timeStamp">true: time gets printed before the message</param>
	static void LogWarning(const std::string& msg, const bool timeStamp = true)
	{
		LogMsg(Level::Warning, msg.c_str(), timeStamp);
	}

	/// <summary>
	/// Prints a warning in the console
	/// </summary>
	/// <param name="msg">the message</param>
	/// <param name="timeStamp">true: time gets printed before the message</param>
	static void LogWarning(const char* msg, const bool timeStamp = true)
	{
		LogMsg(Level::Warning, msg, timeStamp);
	}

	/// <summary>
	/// Throws an error box with a message, different options on box depending on Debug or Release
	/// </summary>
	/// <param name="msg">the message</param>
	/// <param name="timeStamp">true: time gets shown in the error box</param>
	static void LogError(const std::string& msg, const bool timeStamp = true)
	{
		LogMsg(Level::Error, msg.c_str(), timeStamp);
	}

	/// <summary>
	/// Throws an error box with a message, different options on box depending on Debug or Release
	/// </summary>
	/// <param name="msg">the message</param>
	/// <param name="timeStamp">true: time gets shown in the error box</param>
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
			ThrowErrorBox(msg);
		}

	}
	static void ThrowErrorBox(const std::string & message);
};
