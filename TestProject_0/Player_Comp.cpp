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
#include "Transform.h"
#include "WorldTileManager_Comp.h"
#include "DiskManager_Comp.h"
#include "CoilyCreature_Comp.h"

void Player_Comp::Update()
{
	CheckIfDead();
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
}

void Player_Comp::FellOffPyramid()
{
	int tile{ m_pController->GetStandingTileIdx() };
	if(m_pDiskmanager->IsDiskNextToTile(tile))
	{
		Logger::LogInfo("ON DISK");
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
