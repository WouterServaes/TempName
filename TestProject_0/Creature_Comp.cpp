#include "MiniginPCH.h"
#include "Creature_Comp.h"

#include "Scene.h"
#include "CharacterController_Comp.h"
#include "WorldTileManager_Comp.h"

void Creature_Comp::Respawn()
{
	m_pCharacterController->GoToSpawnPos();
}

void Creature_Comp::Start()
{
	m_pCharacterController = GetComponent<CharacterController_Comp>();
	m_pWorldTileManager = m_pGameObject->GetCurrentScene()->GetGameObject("WorldTileManager")->GetComponent<WorldTileManager_Comp>();
	m_pTransform = m_pGameObject->GetTransform();
	Spawn();
}
