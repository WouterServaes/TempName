#include "MiniginPCH.h"
#include "GameController_Comp.h"

#include "AudioServiceLocator.h"
#include "DiskManager_Comp.h"
#include "Events.h"
#include "PlayerManager_Comp.h"
#include "Player_Comp.h"
#include "Scene.h"
#include "Subject.h"
#include "WorldTileManager_Comp.h"

void GameController_Comp::CompletedGrid()
{
	if (m_CurrentLevel == 3)
	{
		CompletedGame();
	}
	else
	{
		auto* pScene{ m_pGameObject->GetCurrentScene() };

		for (auto pl : m_pPlayers)
			pl->GetComponent<Player_Comp>()->NextLevel();

		auto pTileManager{ pScene->GetGameObject("WorldTileManager")->GetComponent<WorldTileManager_Comp>() };
		pTileManager->ResetTiles();

		if (m_CurrentLevel == 1)
			m_CurrentLevel = 2;
		else if (m_CurrentLevel == 2)
			m_CurrentLevel = 3;
	}
	AudioServiceLocator::GetAudio()->PlaySound(3, 100);
}

void GameController_Comp::PlayerDied()
{
	m_PlayerDeadCount++;
	if (m_PlayerDeadCount >= m_pPlayers.size())
	{
		auto* pScene{ m_pGameObject->GetCurrentScene() };
		pScene->GetGameObject("GameOver")->SetActive(true);
		pScene->GetGameObject("GameOverMenu")->SetActive(true);
	}
}

void GameController_Comp::ResetGame()
{
	m_CurrentLevel = 0;
}

void GameController_Comp::Start()
{
	m_pPlayers = m_pGameObject->GetCurrentScene()->GetGameObject("PlayerManager")->GetConstComponent<PlayerManager_Comp>()->GetPlayers();
}

void GameController_Comp::CompletedGame()
{
	const auto* pDiskManager{ m_pGameObject->GetCurrentScene()->GetGameObject("DiskManager")->GetComponent<DiskManager_Comp>() };
	const int remainingDisks{ pDiskManager->GetRemainingDisks() };

	if (remainingDisks > 0)
	{
		for (auto pl : m_pPlayers)
		{
			auto* pPlayerSubject{ pl->GetSubject() };
			for (int idx{}; idx < remainingDisks; idx++)
				pPlayerSubject->Notify(pl.get(), Event::DiskLeftAtEnd);
		}
	}

	auto* pScene{ m_pGameObject->GetCurrentScene() };
	pScene->GetGameObject("Win")->SetActive(true);
	pScene->GetGameObject("WinMenu")->SetActive(true);
	AudioServiceLocator::GetAudio()->PlaySound(3, 100);
}