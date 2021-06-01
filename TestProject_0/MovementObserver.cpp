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
	case Event::MoveLeft:
		MoveLeft(pGameObject);
		break;
	case Event::MoveRight:
		MoveRight(pGameObject);
		break;
	default:;
	}
}

void MovementObserver::MoveLeftUp(GameObject* pGameObject) const
{
	pGameObject->GetComponent<CharacterController_Comp>()->MoveLeftUpOnGrid();
	Logger::LogInfo("leftUp");
}

void MovementObserver::MoveLeftDown(GameObject* pGameObject)const
{
	pGameObject->GetComponent<CharacterController_Comp>()->MoveLeftDownOnGrid();
	Logger::LogInfo("leftDown");
}

void MovementObserver::MoveRightUp(GameObject* pGameObject)const
{
	pGameObject->GetComponent<CharacterController_Comp>()->MoveRightUpOnGrid();
	Logger::LogInfo("rightUp");
}

void MovementObserver::MoveRightDown(GameObject* pGameObject)const
{
	pGameObject->GetComponent<CharacterController_Comp>()->MoveRightDownOnGrid();
	Logger::LogInfo("rightDown");
}

void MovementObserver::MoveRight(GameObject* pGameObject) const
{
	pGameObject->GetComponent<CharacterController_Comp>()->MoveRightOnGrid();
	Logger::LogInfo("right");
}

void MovementObserver::MoveLeft(GameObject* pGameObject) const
{
	pGameObject->GetComponent<CharacterController_Comp>()->MoveLeftOnGrid();
	Logger::LogInfo("left");
}
