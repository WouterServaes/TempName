#pragma once
#include "Singleton.h"
namespace dae
{
	class FpsCounter final:public Singleton<FpsCounter>
	{

	public:
		int fps{};
		void SetFps();
	private:
		float m_ElapsedSec{0.f};
		int m_FrameCount{ 0 };
		friend class Singleton<FpsCounter>;
		FpsCounter() = default;
	};
}

