#include "MiniginPCH.h"
#include "GreenCreature_Comp.h"

#include "Animation_Comp.h"
#include "CharacterController_Comp.h"
#include "Events.h"
#include "Scene.h"
#include "Subject.h"
#include "Transform.h"
#include "WorldTileManager_Comp.h"

GreenCreature_Comp::GreenCreature_Comp(const float timeBetweenJumps) : m_TimeBetweenJumps(timeBetweenJumps)
{
}

void GreenCreature_Comp::UpdateCreature()
{
	if (m_Dead)
		HandleDead();
	else
		HandleAlive();
}

void GreenCreature_Comp::Respawn()
{
	m_pCharacterController->GoToSpawnPos();
	m_Dead = false;
	m_ElapsedTime = 0.f;
	m_pTransform->ScaleUniform(m_origScale);
	m_FollowingSide = (rand() % 2 == 0) ? Transform::Side::Left : Transform::Side::Right;
}

void GreenCreature_Comp::ResetCreature()
{
	Respawn();
}

void GreenCreature_Comp::Spawn()
{
	auto spawnPos{ m_pWorldTileManager->GetTileStandPos(m_pWorldTileManager->GetTileAmount()) };
	m_origScale = m_pTransform->GetUniformScale();

	const auto textureWidth{ GetConstComponent<Animation_Comp>()->GetFrameDimensions().x * m_origScale };
	spawnPos.x -= textureWidth / 2.f;

	m_pCharacterController->SetSpawnPos(spawnPos);
	Respawn();
}

void GreenCreature_Comp::CollidedWithPlayer(const int playerIndex)
{
	if (!m_Dead)
	{
		m_Dead = true;
		m_pTransform->ScaleUniform(0.f);
		m_ElapsedTime = 0.f;
		m_pPlayers.at(playerIndex)->GetSubject()->Notify(m_pPlayers.at(playerIndex).get(), Event::CatchedSlickOrSam);
	}
}

void GreenCreature_Comp::HandleDead()
{
	m_ElapsedTime += Time::GetInstance().deltaTime;
	if (m_ElapsedTime >= m_DeadCooldown)
	{
		Respawn();
	}
}

void GreenCreature_Comp::HandleAlive()
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
			case Transform::Side::Left:
				if (!otherDir)
					m_pCharacterController->MoveLeftDownOnGrid();
				else
					m_pCharacterController->MoveRightDownOnGrid();
				break;
			case Transform::Side::Right:
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