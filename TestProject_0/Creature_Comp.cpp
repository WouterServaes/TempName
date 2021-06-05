#include "MiniginPCH.h"
#include "Creature_Comp.h"

#include "Scene.h"
#include "CharacterController_Comp.h"
#include "WorldTileManager_Comp.h"
#include "Transform.h"

void Creature_Comp::Respawn()
{
	m_pCharacterController->GoToSpawnPos();
}

void Creature_Comp::Update()
{
	UpdateCreature();
	CheckForPlayer();
}

void Creature_Comp::CheckForPlayer()
{
	const int tileIdx{ m_pWorldTileManager->GetTileIdxAtPosition(m_pTransform->GetPosition()) };
	if (tileIdx == -1) return;
	const int playerTileIdx{ m_pWorldTileManager->GetTileIdxAtPosition(m_pPlayer->GetTransform()->GetPosition()) };
	if (playerTileIdx == -1 || playerTileIdx == m_pWorldTileManager->GetTileAmount()) return;
	
	if (tileIdx == playerTileIdx)
	{
		CollidedWithPlayer();
	}
}

void Creature_Comp::Start()
{
	m_pCharacterController = GetComponent<CharacterController_Comp>();
	m_pWorldTileManager = m_pGameObject->GetCurrentScene()->GetGameObject("WorldTileManager")->GetComponent<WorldTileManager_Comp>();
	m_pTransform = m_pGameObject->GetTransform();
	m_pPlayer = m_pGameObject->GetCurrentScene()->GetGameObject("pl");
	Spawn();
}
