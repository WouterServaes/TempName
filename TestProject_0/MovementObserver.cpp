#include "MiniginPCH.h"
#include "MovementObserver.h"


#include "AudioServiceLocator.h"
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
	pGameObject->GetComponent<CharacterController_Comp>()->MoveLeftUpOnGrid();
}

void MovementObserver::MoveLeftDown(GameObject* pGameObject)const
{
	pGameObject->GetComponent<CharacterController_Comp>()->MoveLeftDownOnGrid();
}

void MovementObserver::MoveRightUp(GameObject* pGameObject)const
{
	pGameObject->GetComponent<CharacterController_Comp>()->MoveRightUpOnGrid();
}

void MovementObserver::MoveRightDown(GameObject* pGameObject)const
{
	AudioServiceLocator::GetAudio()->PlaySound(0, 100);

	pGameObject->GetComponent<CharacterController_Comp>()->MoveRightDownOnGrid();
}
