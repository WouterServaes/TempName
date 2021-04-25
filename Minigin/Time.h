#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final:
	    public Singleton<Time>
	{
	public:
		~Time() = default;
		Time(const Time& other) = delete;
		Time(Time&& other) noexcept = delete;
		Time& operator=(const Time& other) = delete;
		Time& operator=(Time&& other) noexcept = delete;
		
		float deltaTime{}, elapsedTime{};
		int fps{};
		
		void Update(const float deltaT)
		{
			deltaTime = deltaT;
			elapsedTime += deltaTime;
			SetFps();
			
		};
	private:
		void SetFps() { fps = int(1.f / deltaTime); };
		friend class Singleton<Time>;
		Time() = default;
	};
}

