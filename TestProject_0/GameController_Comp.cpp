#include "MiniginPCH.h"
#include "GameController_Comp.h"


#include "Player_Comp.h"
#include "Scene.h"
#include "Subject.h"
#include "WorldTileManager_Comp.h"

void GameController_Comp::CompletedGrid()
{
	if(m_CurrentLevel == 3)
	{
		Logger::LogInfo("Completed game");
	}
	else
	{
		auto* pScene{ m_pGameObject->GetCurrentScene() };
		auto pPlayer{ pScene->GetGameObject("pl") };
		pPlayer->GetComponent<Player_Comp>()->NextLevel();
		pScene->GetGameObject("WorldTileManager")->GetComponent<WorldTileManager_Comp>()->ResetTiles();
		
		if (m_CurrentLevel == 1)
			m_CurrentLevel = 2;
		else if (m_CurrentLevel == 2)
			m_CurrentLevel = 3;
	}
}

void GameController_Comp::PlayerDied()
{
	Logger::LogInfo("Player Died");	
}

