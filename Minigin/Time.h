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
		
		void SetFps() { fps = int(1.f / deltaTime); };
	private:
		friend class Singleton<Time>;
		Time() = default;
	};
}

