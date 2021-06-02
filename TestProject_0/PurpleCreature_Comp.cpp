#include "MiniginPCH.h"
#include "PurpleCreature_Comp.h"


#include "Animation_Comp.h"
#include "CharacterController_Comp.h"
#include "Scene.h"
#include "Transform.h"
#include "WorldTileManager_Comp.h"

PurpleCreature_Comp::PurpleCreature_Comp(const float timeBetweenJumps) : m_TimeBetweenJumps(timeBetweenJumps)
{
}

void PurpleCreature_Comp::Start()
{
	m_pCharacterController = GetComponent<CharacterController_Comp>();
	m_pWorldTileManager = m_pGameObject->GetCurrentScene()->GetGameObject("WorldTileManager")->GetComponent<WorldTileManager_Comp>();
	m_pTransform = m_pGameObject->GetTransform();
	Spawn();
}

void PurpleCreature_Comp::Update()
{
	if (m_pCharacterController->CanMove())
	{
		m_ElapsedTime += Time::GetInstance().deltaTime;
		if (m_ElapsedTime >= m_TimeBetweenJumps)
		{
			m_ElapsedTime = 0.f;
			switch (m_FollowingSide)
			{
			case Side::Left:
				m_pCharacterController->MoveLeftDownOnGrid();
				break;
			case Side::Right:
				m_pCharacterController->MoveRightDownOnGrid();
				break;
			default:;
			}
		}
	}
}

void PurpleCreature_Comp::Spawn()
{
	//m_FollowingSide = (rand() % 2 == 0) ? Side::Left : Side::Right;
	//m_FollowingSide = Side::Right;
	//const int tileNr{ (m_FollowingSide == Side::Left) ? 0 : m_pWorldTileManager->GetBottomRowAmount() };

	auto spawnPos{ m_pWorldTileManager->GetTileStandPos(m_pWorldTileManager->GetTileAmount()) };

	const auto textureWidth{ GetConstComponent<Animation_Comp>()->GetFrameDimensions().x * m_pTransform->GetUniformScale() };
	spawnPos.x -= textureWidth / 2.f;
	
	m_pCharacterController->SetSpawnPos(spawnPos);
	m_pTransform->SetPosition(spawnPos.x, spawnPos.y);
}