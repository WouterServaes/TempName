#include "MiniginPCH.h"
#include "PurpleCreature_Comp.h"

#include "Animation_Comp.h"
#include "CharacterController_Comp.h"
#include "Events.h"
#include "Subject.h"
#include "Time.h"
#include "WorldTileManager_Comp.h"

PurpleCreature_Comp::PurpleCreature_Comp(const Transform::Side spawnSide, const float timeBetweenJumps) : m_SpawnSide(spawnSide),
m_TimeBetweenJumps(timeBetweenJumps)
{
}

void PurpleCreature_Comp::UpdateCreature()
{
	if (m_WantsToSpawn)
	{
		TryToActuallyRespawn();
	}
	else if (m_pCharacterController->CanMove())
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

void PurpleCreature_Comp::Respawn()
{
	if(!m_WantsToSpawn)
	{
		m_WantsToSpawn = true;
		m_CollisionWithPlayerEnabled = false;
		m_pTransform->ScaleUniform(0.f);
	}
}

void PurpleCreature_Comp::Spawn()
{
	int tileNr{ 0 };
	if (m_SpawnSide == Transform::Side::Right) tileNr = m_pWorldTileManager->GetBottomRowAmount();

	auto spawnPos{ m_pWorldTileManager->GetTileStandPos(tileNr) };

	const auto textureWidth{ GetConstComponent<Animation_Comp>()->GetFrameDimensions().x * m_pTransform->GetUniformScale() };
	spawnPos.x -= textureWidth / 2.f;
	m_pCharacterController->SetSpawnPos(spawnPos);
	m_SpawnTileIdx = m_pWorldTileManager->GetTileIdxAtPosition(spawnPos);
	m_OriginalScale = m_pTransform->GetUniformScale();
	Respawn();
}

void PurpleCreature_Comp::CollidedWithPlayer(const int playerIndex)
{
	const int spawnTileIdx{ m_pWorldTileManager->GetTileIdxAtPosition(m_pCharacterController->GetSpawnPos()) };
	const int currentTileIdx{ m_pWorldTileManager->GetTileIdxAtPosition(m_pTransform->GetPosition()) };
	if (spawnTileIdx == currentTileIdx) Respawn();
	else
	m_pPlayers.at(playerIndex)->GetSubject()->Notify(m_pPlayers.at(playerIndex).get(), Event::AttackedByPurple);
}

void PurpleCreature_Comp::TryToActuallyRespawn()
{
	const int spawnTileIdx{ m_pWorldTileManager->GetTileIdxAtPosition(m_pCharacterController->GetSpawnPos()) };
	bool canRespawn{ true };
	for(const auto& player: m_pPlayers)
	{
		if (spawnTileIdx == m_pWorldTileManager->GetTileIdxAtPosition(player->GetTransform()->GetPosition()))
		{
			canRespawn = false;
			break;
		}
	}

	if(canRespawn)
	{
		m_WantsToSpawn = false;
		m_CollisionWithPlayerEnabled = true;
		m_pTransform->ScaleUniform(m_OriginalScale);
		m_pCharacterController->GoToSpawnPos();
	}
}
