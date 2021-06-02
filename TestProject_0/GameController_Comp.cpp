#include "MiniginPCH.h"
#include "GameController_Comp.h"

void GameController_Comp::CompletedGrid()
{
	Logger::LogInfo("Completed Grid");
}

void GameController_Comp::PlayerDied()
{
	Logger::LogInfo("Player Died");	
}

void GameController_Comp::StartLevelTwo()
{
	m_CurrentLevel = 2;
}

void GameController_Comp::StartLevelThree()
{
	m_CurrentLevel = 3;
}
