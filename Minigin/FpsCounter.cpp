#include "MiniginPCH.h"
#include "FpsCounter.h"
#include "Time.h"

void dae::FpsCounter::SetFps()
{
	fps = int(1.f / Time::GetInstance().deltaTime);
	
	//m_FrameCount+=1;
	//m_ElapsedSec += Time::GetInstance().deltaTime;
	//if(m_ElapsedSec >= 1.f)
	//{
	//	fps = m_FrameCount;
	//	m_FrameCount = 0;
	//	m_ElapsedSec = 0.f;
	//}

}