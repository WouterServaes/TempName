#include "MiniginPCH.h"
#include "PurpleCreature_Comp.h"

#include "Animation_Comp.h"
#include "CharacterController_Comp.h"
#include "Events.h"
#include "Subject.h"
#include "WorldTileManager_Comp.h"

PurpleCreature_Comp::PurpleCreature_Comp(const Transform::Side spawnSide, const float timeBetweenJumps) : m_SpawnSide(spawnSide),
	m_TimeBetweenJumps(timeBetweenJumps)
{
}

void PurpleCreature_Comp::UpdateCreature()
{
	if (m_pCharacterController->CanMove())
	{
		m_ElapsedTime += Time::GetInstance().deltaTime;
		if (m_ElapsedTime >= m_TimeBetweenJumps)
		{
			m_ElapsedTime = 0.f;
			const bool otherDir{ rand() % 10 <= 3 };
			switch (m_SpawnSide)
			{
			case Transform::Side::Left:
				if (!otherDir)
					m_pCharacterController->MoveRightUpOnGrid();
				else
					m_pCharacterController->MoveLeftUpOnGrid();
				break;
			case Transform::Side::Right:
				if (!otherDir)
					m_pCharacterController->MoveLeftDownOnGrid();
				else
					m_pCharacterController->MoveRightUpOnGrid();
				break;
			default:;
			}
		}
	}
}

void PurpleCreature_Comp::ResetCreature()
{
	m_ElapsedTime = 0.f;
	Respawn();
}

void PurpleCreature_Comp::Spawn()
{
	int tileNr{ 0 };
	if (m_SpawnSide == Transform::Side::Right) tileNr = m_pWorldTileManager->GetBottomRowAmount();

	auto spawnPos{ m_pWorldTileManager->GetTileStandPos(tileNr) };

	const auto textureWidth{ GetConstComponent<Animation_Comp>()->GetFrameDimensions().x * m_pTransform->GetUniformScale() };
	spawnPos.x -= textureWidth / 2.f;
	m_pCharacterController->SetSpawnPos(spawnPos);
	Respawn();
}

void PurpleCreature_Comp::CollidedWithPlayer(const int playerIndex)
{
	m_pPlayers.at(playerIndex)->GetSubject()->Notify(m_pPlayers.at(playerIndex).get(), Event::AttackedByPurple);
}
