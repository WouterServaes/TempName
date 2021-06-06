#include "MiniginPCH.h"
#include "CoilyMover.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/gtx/norm.hpp>
#pragma warning(pop)

#include "CharacterController_Comp.h"
#include "Transform.h"

CoilyAi::CoilyAi(const std::vector<Transform*>& playerTransforms, int* pDefeatedPlayerByIndex,
	Transform* pCoilyTransform, CharacterController_Comp* pCoilyCharController) : m_pPlayersTransform(playerTransforms), m_pDefeatedByPlayerIndex(pDefeatedPlayerByIndex), m_pCoilyTransform(pCoilyTransform), m_pCoilyCharacterController(pCoilyCharController)
{
}

void CoilyAi::Mover(const bool goToDisk, const glm::vec2 diskPos)
{
	const auto& coilyPos{ m_pCoilyTransform->GetPosition() };
	glm::vec2 goToPos;
	if (goToDisk)
		goToPos = diskPos;
	else
	{
		float smallestDist{ FLT_MAX };
		glm::vec3 closestPos{};

		const int playerCount{ static_cast<int>(m_pPlayersTransform.size()) };
		for (int idx{}; idx < playerCount; idx++)
		{
			const auto playerPos{ m_pPlayersTransform.at(idx)->GetPosition() };
			const float dist{ glm::distance2(coilyPos, playerPos) };
			if (dist < smallestDist)
			{
				closestPos = playerPos;
				smallestDist = dist;
				*m_pDefeatedByPlayerIndex = idx;
			}
		}
		goToPos = closestPos;
	}

	bool moveLeft{ true };

	//decide direction
	if (goToPos.x > coilyPos.x) //move right
		moveLeft = false;
	else if (goToPos.x == coilyPos.x)//move left or right
		moveLeft = rand() % 10 < 5;

	bool moveUp{ true };
	if (goToPos.y > coilyPos.y) //move down
		moveUp = false;
	else if (goToPos.y == coilyPos.y)//move up or down
		moveUp = rand() % 10 < 5;

	//move in said direction
	if (moveLeft)
	{
		if (moveUp)
			m_pCoilyCharacterController->MoveLeftUpOnGrid();
		else
			m_pCoilyCharacterController->MoveLeftDownOnGrid();
	}
	else
	{
		if (moveUp)
			m_pCoilyCharacterController->MoveRightUpOnGrid();
		else
			m_pCoilyCharacterController->MoveRightDownOnGrid();
	}
}
