#include "MiniginPCH.h"
#include "Player_Comp.h"

#include "Animation_Comp.h"
#include "CharacterController_Comp.h"
#include "MoveCommands.h"
#include "InputManager.h"
#include "Scene.h"
#include "Transform.h"
#include "WorldTileManager_Comp.h"

void Player_Comp::Update()
{

}

void Player_Comp::Start()
{
	m_pController = GetComponent<CharacterController_Comp>();
	InitInput();

	const auto pWorldGrid{ m_pGameObject->GetCurrentScene()->GetGameObject("WorldTileManager") };
	const auto pWorldGridManagerComp{ pWorldGrid->GetConstComponent<WorldTileManager_Comp>() };
	auto spawnPos{ pWorldGridManagerComp->GetTileStandPos(pWorldGridManagerComp->GetTileAmount()) };

	auto* pTransform{ m_pGameObject->GetTransform() };
	const auto textureWidth{ GetConstComponent<Animation_Comp>()->GetFrameDimensions().x * pTransform->GetUniformScale() };

	spawnPos.x -= textureWidth / 2.f;
	pTransform->SetPosition(spawnPos.x, spawnPos.y);
	m_pGameObject->GetComponent<CharacterController_Comp>()->SetSpawnPos(spawnPos);
	
}

void Player_Comp::InitInput()
{
	InputManager::GetInstance().AssignKey(InputAction(SDLK_UP, TriggerState::Released, ControllerButtons::ButtonUp), std::make_unique<Command_MoveLeftUp>(m_pGameObject));
	InputManager::GetInstance().AssignKey(InputAction(SDLK_DOWN, TriggerState::Released, ControllerButtons::ButtonDown), std::make_unique<Command_MoveLeftDown>(m_pGameObject));
	InputManager::GetInstance().AssignKey(InputAction(SDLK_LEFT, TriggerState::Released, ControllerButtons::ButtonLeft), std::make_unique<Command_MoveRightUp>(m_pGameObject));
	InputManager::GetInstance().AssignKey(InputAction(SDLK_RIGHT, TriggerState::Released, ControllerButtons::ButtonRight), std::make_unique<Command_MoveRightDown>(m_pGameObject));
}
