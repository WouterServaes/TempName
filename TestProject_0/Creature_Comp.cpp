#include "MiniginPCH.h"
#include "Creature_Comp.h"

#include "Scene.h"
#include "CharacterController_Comp.h"
#include "PlayerManager_Comp.h"
#include "WorldTileManager_Comp.h"
#include "Transform.h"

void Creature_Comp::Respawn()
{
	m_pCharacterController->GoToSpawnPos();
}

void Creature_Comp::Update()
{
	UpdateCreature();
	if(m_CollisionWithPlayerEnabled)
		CheckForPlayer();
}

void Creature_Comp::CheckForPlayer()
{
	const int tileIdx{ m_pWorldTileManager->GetTileIdxAtPosition(m_pTransform->GetPosition()) };
	if (tileIdx == -1) return;

	const int playerCount{ static_cast<int>(m_pPlayers.size()) };
	for (int idx{}; idx < playerCount; idx++)
	{
		const int playerTileIdx{ m_pWorldTileManager->GetTileIdxAtPosition(m_pPlayers.at(idx)->GetTransform()->GetPosition()) };
		if (playerTileIdx == -1 || playerTileIdx == m_pWorldTileManager->GetTileAmount()) return;

		if (tileIdx == playerTileIdx)
		{
			CollidedWithPlayer(idx);
			break;
		}
	}
}

void Creature_Comp::Start()
{
	m_pCharacterController = GetComponent<CharacterController_Comp>();
	m_pWorldTileManager = m_pGameObject->GetCurrentScene()->GetGameObject("WorldTileManager")->GetComponent<WorldTileManager_Comp>();
	m_pTransform = m_pGameObject->GetTransform();
	m_pPlayers = m_pGameObject->GetCurrentScene()->GetGameObject("PlayerManager")->GetComponent<PlayerManager_Comp>()->GetPlayers();
	Spawn();
}