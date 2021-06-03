#include "MiniginPCH.h"
#include "CoilyCreature_Comp.h"


#include "Animation_Comp.h"
#include "CharacterController_Comp.h"
#include "Events.h"
#include "Subject.h"
#include "Transform.h"
#include "WorldTileManager_Comp.h"

CoilyCreature_Comp::CoilyCreature_Comp(const float timeBetweenJumps, const std::string& coilyAnimationSheet, const int coilyImageAmount, const int coilyFramesPerSecond, const glm::vec2 coilyFrameDimensions):
	m_TimeBetweenJumps(timeBetweenJumps), m_CoilyImageAmount(coilyImageAmount), m_CoilyFPS(coilyFramesPerSecond), m_CoilyAnimSheet(coilyAnimationSheet), m_CoilyFrameDim(coilyFrameDimensions)
{
}

void CoilyCreature_Comp::Spawn()
{
	auto spawnPos{ m_pWorldTileManager->GetTileStandPos(m_pWorldTileManager->GetTileAmount()) };

	const auto textureWidth{ GetConstComponent<Animation_Comp>()->GetFrameDimensions().x * m_pTransform->GetUniformScale() };
	spawnPos.x -= textureWidth / 2.f;

	m_pCharacterController->SetSpawnPos(spawnPos);
	Respawn();
}

void CoilyCreature_Comp::UpdateCreature()
{
	if (m_IsEgg)
		UpdateEgg();
	else
		FollowPlayer();
}

void CoilyCreature_Comp::CollidedWithPlayer()
{
	if(!m_IsEgg) m_pPlayer->GetSubject()->Notify(m_pPlayer.get(), Event::AttackedByPurple);
}

void CoilyCreature_Comp::UpdateEgg()
{
	BounceToBottom();

	const int tileIdx{ m_pWorldTileManager->GetTileIdxAtPosition(m_pTransform->GetPosition()) };
	
	if (tileIdx >= 0 && tileIdx <= m_pWorldTileManager->GetBottomRowAmount())
		ChangeToSnake();
}

void CoilyCreature_Comp::BounceToBottom()
{
	if(m_pCharacterController->CanMove())
	{
		m_ElapsedTime += Time::GetInstance().deltaTime;
		if (m_ElapsedTime >= m_TimeBetweenJumps)
		{
			m_ElapsedTime = 0.f;
			const Side side = (m_LastSide == Side::Left) ? Side::Right : Side::Left;
			if (side == Side::Left)
				m_pCharacterController->MoveLeftDownOnGrid();
			else
				m_pCharacterController->MoveRightDownOnGrid();
			m_LastSide = side;
		}
	}
}

void CoilyCreature_Comp::ChangeToSnake()
{
	m_IsEgg = false;
	m_pTransform->ScaleUniform(.45f);
	GetComponent<Animation_Comp>()->UpdateAnimationSheet(m_CoilyAnimSheet, m_CoilyImageAmount, m_CoilyFPS, m_CoilyFrameDim);
}

void CoilyCreature_Comp::FollowPlayer()
{
}
