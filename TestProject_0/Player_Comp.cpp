#include "MiniginPCH.h"
#include "Player_Comp.h"

#include "Animation_Comp.h"
#include "AudioServiceLocator.h"
#include "CharacterController_Comp.h"
#include "GameController_Comp.h"
#include "Health_Comp.h"
#include "MoveCommands.h"
#include "InputManager.h"
#include "Scene.h"
#include "Score_Comp.h"
#include "TileChanger_Comp.h"

#include "DiskManager_Comp.h"
#include "CoilyCreature_Comp.h"

void Player_Comp::Update()
{
	if(!m_IsDead)CheckIfDead();
}

void Player_Comp::Start()
{
	m_pController = GetComponent<CharacterController_Comp>();
	m_pHealthComp = GetComponent<Health_Comp>();
	m_pDiskmanager = m_pGameObject->GetCurrentScene()->GetGameObject("DiskManager")->GetComponent<DiskManager_Comp>();
	m_pCoily = m_pGameObject->GetCurrentScene()->GetGameObject("Coily")->GetComponent<CoilyCreature_Comp>();
	InitInput();
}

void Player_Comp::NextLevel()
{
	GetComponent<TileChanger_Comp>()->NextLevel();
	m_pController->GoToSpawnPos();
	m_pCoily->ResetCreature();
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
	m_IsDead = false;
}

void Player_Comp::FellOffPyramid()
{
	int tile{ m_pController->GetStandingTileIdx() };
	if (m_pDiskmanager->IsDiskNextToTile(tile))
	{
		m_pCoily->PlayerJumpedOnDisk(m_pDiskmanager->GetDiskPositionNextToTile(tile));
	}
	else
	{
		m_pHealthComp->RemoveLives();
		AudioServiceLocator::GetAudio()->PlaySound(1, 100);
	}
}

void Player_Comp::InitInput()
{
	auto& pInputManager{ m_pGameObject->GetCurrentScene()->GetInputManager() };
	if (m_PlayerIndex == 0)
	{
		pInputManager->AssignKey(InputAction(SDLK_UP, TriggerState::Released, ControllerButtons::ButtonUp), std::make_unique<Command_MoveLeftUp>(m_pGameObject));
		pInputManager->AssignKey(InputAction(SDLK_DOWN, TriggerState::Released, ControllerButtons::ButtonDown), std::make_unique<Command_MoveLeftDown>(m_pGameObject));
		pInputManager->AssignKey(InputAction(SDLK_LEFT, TriggerState::Released, ControllerButtons::ButtonLeft), std::make_unique<Command_MoveRightUp>(m_pGameObject));
		pInputManager->AssignKey(InputAction(SDLK_RIGHT, TriggerState::Released, ControllerButtons::ButtonRight), std::make_unique<Command_MoveRightDown>(m_pGameObject));
	}
	else
	{
		pInputManager->AssignKey(InputAction(SDLK_w, TriggerState::Released, ControllerButtons::ButtonUp, 1), std::make_unique<Command_MoveLeftUp>(m_pGameObject));
		pInputManager->AssignKey(InputAction(SDLK_s, TriggerState::Released, ControllerButtons::ButtonDown, 1), std::make_unique<Command_MoveLeftDown>(m_pGameObject));
		pInputManager->AssignKey(InputAction(SDLK_a, TriggerState::Released, ControllerButtons::ButtonLeft, 1), std::make_unique<Command_MoveRightUp>(m_pGameObject));
		pInputManager->AssignKey(InputAction(SDLK_d, TriggerState::Released, ControllerButtons::ButtonRight, 1), std::make_unique<Command_MoveRightDown>(m_pGameObject));
	}
}

void Player_Comp::CheckIfDead()
{
	if (m_pHealthComp->IsDead())
	{
		m_IsDead = true;
		const auto pGameController{ m_pGameObject->GetCurrentScene()->GetGameObject("GameController") };
		pGameController->GetComponent<GameController_Comp>()->PlayerDied();
		m_pController->SetCanMove(false);
	}
}