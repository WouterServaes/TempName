#include "MiniginPCH.h"
#include "CharacterController_Comp.h"

#include "Transform.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/norm.hpp>

#include "Events.h"
#include "Scene.h"
#include "Subject.h"
#include "WorldTileManager_Comp.h"
#pragma warning(pop)

CharacterController_Comp::CharacterController_Comp(const float moveSpeed)
	: m_MoveSpeed(moveSpeed)
{
}

void CharacterController_Comp::Move(const glm::vec2 movement)
{
	if (!m_IsMoving)
	{
		m_IsMoving = true;
		const auto& pos{ m_pTransform->GetPosition() };
		m_OrigPos = glm::vec2(pos.x, pos.y);
		m_TargetPos = m_OrigPos + movement;
		m_DistanceToTravelSqred = glm::distance2(m_TargetPos, m_OrigPos);
	}
}

void CharacterController_Comp::Update()
{
	if (m_IsMoving)
		UpdatePos();
	
	TestIsOutsideGrid();
}

void CharacterController_Comp::Start()
{
	const auto pWorldGrid{ m_pGameObject->GetCurrentScene()->GetGameObject("WorldTileManager") };
	m_pWorldTileManager = pWorldGrid->GetConstComponent<WorldTileManager_Comp>();
	m_pTransform = m_pGameObject->GetTransform();
	SetGridMovement();
}

void CharacterController_Comp::MoveLeftUpOnGrid()
{
	Move(glm::vec2(m_GridMovements.Left, m_GridMovements.Up));
}

void CharacterController_Comp::MoveLeftDownOnGrid()
{
	Move(glm::vec2(m_GridMovements.Left, m_GridMovements.Down));
}

void CharacterController_Comp::MoveRightUpOnGrid()
{
	Move(glm::vec2(m_GridMovements.Right, m_GridMovements.Up));
}

void CharacterController_Comp::MoveRightDownOnGrid()
{
	Move(glm::vec2(m_GridMovements.Right, m_GridMovements.Down));
}

void CharacterController_Comp::MoveLeftOnGrid()
{
	Move(glm::vec2(m_GridMovements.Left * 2.f, 0.f));
}

void CharacterController_Comp::MoveRightOnGrid()
{
	Move(glm::vec2(m_GridMovements.Right * 2.f, 0.f));
}

bool CharacterController_Comp::GetReachedPos() const
{
	const auto& currentPos{ m_pTransform->GetPosition() };
	const auto distanceTraveledSqred{ glm::distance2(m_OrigPos, glm::vec2(currentPos)) };
	return distanceTraveledSqred >= m_DistanceToTravelSqred;
}

void CharacterController_Comp::UpdatePos()
{
	if (!GetReachedPos())
	{
		//change to bezier curve later https://gamedev.stackexchange.com/questions/157642/moving-a-2d-object-along-circular-arc-between-two-points
		const auto elapsedSec{ Time::GetInstance().elapsedTime };
		m_MoveDelta += elapsedSec * m_MoveSpeed;

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

void CharacterController_Comp::SetGridMovement()
{
	const auto tileDimensions{ m_pWorldTileManager->GetGridTileDimensions() };

	m_GridMovements.Down = tileDimensions.y * 2.f;
	m_GridMovements.Up = -tileDimensions.y * 2.f;
	m_GridMovements.Left = -tileDimensions.x;
	m_GridMovements.Right = tileDimensions.x;
}

void CharacterController_Comp::TestIsOutsideGrid() const
{
	if (!m_pWorldTileManager->IsTileAtPosition(m_TargetPos))
	{
		auto* pSubject{ m_pGameObject->GetSubject() };
		if (pSubject) pSubject->Notify(m_pGameObject, Event::FellOffGrid);
	}
}