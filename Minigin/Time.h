#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final:
	    public Singleton<Time>
	{
	public:
		float deltaTime{};
		int fps{};
		
		void Update(float deltaT)
		{
			deltaTime = deltaT;
			SetFps();
		}
	private:
		friend class Singleton<Time>;
		Time() = default;
		void SetFps() { fps = int(1.f / deltaTime); };
	};
}

