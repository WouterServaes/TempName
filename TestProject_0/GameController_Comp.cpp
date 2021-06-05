#include "MiniginPCH.h"
#include "GameController_Comp.h"

#include "AudioServiceLocator.h"
#include "DiskManager_Comp.h"
#include "Events.h"
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

		m_pPlayer = pScene->GetGameObject("pl");
		m_pPlayer->GetComponent<Player_Comp>()->NextLevel();

		auto pTileManager{ pScene->GetGameObject("WorldTileManager")->GetComponent<WorldTileManager_Comp>() };
		pTileManager->ResetTiles();

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

void GameController_Comp::CompletedGame()
{
	const auto* pDiskManager{ m_pGameObject->GetCurrentScene()->GetGameObject("DiskManager")->GetComponent<DiskManager_Comp>() };
	const int remainingDisks{ pDiskManager->GetRemainingDisks() };

	if (remainingDisks > 0)
	{
		auto* pPlayerSubject{ m_pPlayer->GetSubject() };
		for (int idx{}; idx < remainingDisks; idx++)
			pPlayerSubject->Notify(m_pPlayer.get(), Event::DiskLeftAtEnd);
	}

	auto* pScene{ m_pGameObject->GetCurrentScene() };
	pScene->GetGameObject("Win")->SetActive(true);
	pScene->GetGameObject("WinMenu")->SetActive(true);
	AudioServiceLocator::GetAudio()->PlaySound(3, 100);
}