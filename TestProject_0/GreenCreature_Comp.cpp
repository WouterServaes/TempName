#include "MiniginPCH.h"
#include "GreenCreature_Comp.h"

#include "Animation_Comp.h"
#include "CharacterController_Comp.h"
#include "Transform.h"
#include "WorldTileManager_Comp.h"

GreenCreature_Comp::GreenCreature_Comp(const float timeBetweenJumps) : m_TimeBetweenJumps(timeBetweenJumps)
{
}

void GreenCreature_Comp::Update()
{
	if (m_pCharacterController->CanMove())
	{
		m_ElapsedTime += Time::GetInstance().deltaTime;
		if (m_ElapsedTime >= m_TimeBetweenJumps)
		{
			m_ElapsedTime = 0.f;
			bool otherDir{ rand() % 10 <= 3 };
			switch (m_FollowingSide)
			{
			case Side::Left:
				if (!otherDir)
					m_pCharacterController->MoveLeftDownOnGrid();
				else
					m_pCharacterController->MoveRightDownOnGrid();
				break;
			case Side::Right:
				if (!otherDir)
					m_pCharacterController->MoveRightDownOnGrid();
				else
					m_pCharacterController->MoveLeftDownOnGrid();
				break;
			default:;
			}
		}
	}
}

void GreenCreature_Comp::Respawn()
{
	m_pCharacterController->GoToSpawnPos();

	m_FollowingSide = (rand() % 2 == 0) ? Side::Left : Side::Right;
}

void GreenCreature_Comp::Spawn()
{
	Respawn();
	auto spawnPos{ m_pWorldTileManager->GetTileStandPos(m_pWorldTileManager->GetTileAmount()) };

	const auto textureWidth{ GetConstComponent<Animation_Comp>()->GetFrameDimensions().x * m_pTransform->GetUniformScale() };
	spawnPos.x -= textureWidth / 2.f;

	m_pCharacterController->SetSpawnPos(spawnPos);
	m_pTransform->SetPosition(spawnPos.x, spawnPos.y);
}