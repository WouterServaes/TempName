#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final:
	    public Singleton<Time>
	{
	public:
		float deltaTime{}, elapsedTime{};
		int fps{};
		
		void Update(float deltaT)
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

