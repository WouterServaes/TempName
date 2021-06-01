#include "MiniginPCH.h"
#include "CharacterController_Comp.h"

#include "Transform.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/norm.hpp>
#pragma warning(pop)

CharacterController_Comp::CharacterController_Comp(const float moveSpeed)
	: m_MoveSpeed(moveSpeed)
{
}

void CharacterController_Comp::Move(const glm::vec2 position)
{
	if (!m_IsMoving)
	{
		m_IsMoving = true;
		const auto& pos{ m_pTransform->GetPosition() };
		m_OrigPos = glm::vec2(pos.x, pos.y);
		m_TargetPos = m_OrigPos + position;
		//m_DistanceToTravelSqred = std::pow(m_TargetPos.x - m_OrigPos.x, 2.f) + std::pow(m_TargetPos.y - m_OrigPos.y, 2.f); //distance squared to avoid sqrt
		m_DistanceToTravelSqred = glm::distance2(m_TargetPos, m_OrigPos);
	}
}

void CharacterController_Comp::Update()
{
	if (m_IsMoving)
		UpdatePos();
}

void CharacterController_Comp::Start()
{
	m_pTransform = m_pGameObject->GetTransform();
}

bool CharacterController_Comp::GetReachedPos() const
{
	const auto& currentPos{ m_pTransform->GetPosition() };
	//const auto distanceTraveledSqred{ std::pow(m_OrigPos.x - currentPos.x, 2.f) + std::pow(m_OrigPos.y - currentPos.y, 2.f) };
	const auto distanceTraveledSqred{ glm::distance2(m_OrigPos, glm::vec2(currentPos))};
	return distanceTraveledSqred >= m_DistanceToTravelSqred;
}

void CharacterController_Comp::UpdatePos()
{
	if (!GetReachedPos())
	{
		//change to bezier curve later https://gamedev.stackexchange.com/questions/157642/moving-a-2d-object-along-circular-arc-between-two-points
		const auto elapsedSec{ Time::GetInstance().elapsedTime };
		m_MoveDelta += elapsedSec * m_MoveSpeed;
		//const auto x{ (1 - m_MoveDelta) * m_OrigPos.x + m_MoveDelta * m_TargetPos.x },
		//	y{ (1 - m_MoveDelta) * m_OrigPos.y + m_MoveDelta * m_TargetPos.y };

		const auto lerped{ glm::lerp(m_OrigPos, m_TargetPos, m_MoveDelta) };
		
		m_pTransform->SetPosition(lerped.x, lerped.y);
	}
	else
	{
		m_IsMoving = false;
		m_MoveDelta = 0.f;
		m_DistanceToTravelSqred = 0.f;
		m_pTransform->SetPosition(m_TargetPos.x, m_TargetPos.y);
	}
}