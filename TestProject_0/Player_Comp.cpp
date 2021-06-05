#include "MiniginPCH.h"
#include "Player_Comp.h"

#include "Animation_Comp.h"
#include "AudioServiceLocator.h"
#include "CharacterController_Comp.h"
#include "Events.h"
#include "GameController_Comp.h"
#include "Health_Comp.h"
#include "MoveCommands.h"
#include "InputManager.h"
#include "Scene.h"
#include "Score_Comp.h"
#include "TileChanger_Comp.h"
#include "Transform.h"
#include "WorldTileManager_Comp.h"

void Player_Comp::Update()
{
	CheckIfDead();
}

void Player_Comp::Start()
{
	m_pController = GetComponent<CharacterController_Comp>();
	m_pHealthComp = GetComponent<Health_Comp>();
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

void Player_Comp::NextLevel()
{
	GetComponent<TileChanger_Comp>()->NextLevel();
	m_pController->GoToSpawnPos();
}

void Player_Comp::ResetPlayer()
{
	//health reset
	m_pHealthComp->ResetHealth();
	//score reset
	GetComponent<Score_Comp>()->ResetScore();
	//position reset
	m_pController->GoToSpawnPos();
	//can move = true
	m_pController->SetCanMove(true);
}

void Player_Comp::FellOffPyramid() const
{
	m_pHealthComp->RemoveLives();
	AudioServiceLocator::GetAudio()->PlaySound(1, 100);
}

void Player_Comp::InitInput()
{
	InputManager::GetInstance().AssignKey(InputAction(SDLK_UP, TriggerState::Released, ControllerButtons::ButtonUp), std::make_unique<Command_MoveLeftUp>(m_pGameObject));
	InputManager::GetInstance().AssignKey(InputAction(SDLK_DOWN, TriggerState::Released, ControllerButtons::ButtonDown), std::make_unique<Command_MoveLeftDown>(m_pGameObject));
	InputManager::GetInstance().AssignKey(InputAction(SDLK_LEFT, TriggerState::Released, ControllerButtons::ButtonLeft), std::make_unique<Command_MoveRightUp>(m_pGameObject));
	InputManager::GetInstance().AssignKey(InputAction(SDLK_RIGHT, TriggerState::Released, ControllerButtons::ButtonRight), std::make_unique<Command_MoveRightDown>(m_pGameObject));
}

void Player_Comp::CheckIfDead() const
{
	if(m_pHealthComp->IsDead())
	{
		const auto pGameController{ m_pGameObject->GetCurrentScene()->GetGameObject("GameController") };
		pGameController->GetComponent<GameController_Comp>()->PlayerDied();
		m_pController->SetCanMove(false);
	}
}
