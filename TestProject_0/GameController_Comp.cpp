#include "MiniginPCH.h"
#include "GameController_Comp.h"



#include "AudioServiceLocator.h"
#include "Player_Comp.h"
#include "Scene.h"
#include "WorldTileManager_Comp.h"

void GameController_Comp::CompletedGrid()
{
	if(m_CurrentLevel == 3)
	{
		auto* pScene{ m_pGameObject->GetCurrentScene() };
		pScene->GetGameObject("Win")->SetActive(true);
		pScene->GetGameObject("WinMenu")->SetActive(true);
		AudioServiceLocator::GetAudio()->PlaySound(3, 100);
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
	auto* pScene{ m_pGameObject->GetCurrentScene() };
	pScene->GetGameObject("GameOver")->SetActive(true);
	pScene->GetGameObject("GameOverMenu")->SetActive(true);
}

void GameController_Comp::ResetGame()
{
	m_CurrentLevel = 0;
}

