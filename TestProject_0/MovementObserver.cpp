#include "MiniginPCH.h"
#include "MovementObserver.h"

#include "CharacterController_Comp.h"
#include "Events.h"
#include "GameObject.h"

void MovementObserver::OnNotify(GameObject* const pGameObject, const Event event)
{
	switch (event)
	{
	case Event::MoveLeftUp:
		MoveLeftUp(pGameObject);
		break;
	case Event::MoveLeftDown:
		MoveLeftDown(pGameObject);
		break;
	case Event::MoveRightUp:
		MoveRightUp(pGameObject);
		break;
	case Event::MoveRightDown:
		MoveRightDown(pGameObject);
		break;
	default:;
	}
}

void MovementObserver::MoveLeftUp(GameObject* pGameObject) const
{
	pGameObject->GetComponent<CharacterController_Comp>()->Move(glm::vec2(-10, 10));
}

void MovementObserver::MoveLeftDown(GameObject* pGameObject)const
{
	pGameObject->GetComponent<CharacterController_Comp>()->Move(glm::vec2(0, 0));
}

void MovementObserver::MoveRightUp(GameObject* pGameObject)const
{
	pGameObject->GetComponent<CharacterController_Comp>()->Move(glm::vec2(0, 0));
}

void MovementObserver::MoveRightDown(GameObject* pGameObject)const
{
	pGameObject->GetComponent<CharacterController_Comp>()->Move(glm::vec2(0, 0));
}