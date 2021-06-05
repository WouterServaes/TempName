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
	 auto* pCharContr{ pGameObject->GetComponent<CharacterController_Comp>() };
	 if (pCharContr->CanMove())
		 PlayMoveSound();
	
	pCharContr->MoveLeftUpOnGrid();
}

void MovementObserver::MoveLeftDown(GameObject* pGameObject)const
{
	auto* pCharContr{ pGameObject->GetComponent<CharacterController_Comp>() };
	if (pCharContr->CanMove())
		PlayMoveSound();
	pCharContr->MoveLeftDownOnGrid();
}

void MovementObserver::MoveRightUp(GameObject* pGameObject)const
{
	auto* pCharContr{ pGameObject->GetComponent<CharacterController_Comp>() };
	if (pCharContr->CanMove())
		PlayMoveSound();
	pCharContr->MoveRightUpOnGrid();
}

void MovementObserver::MoveRightDown(GameObject* pGameObject)const
{
	auto* pCharContr{ pGameObject->GetComponent<CharacterController_Comp>() };
	if (pCharContr->CanMove())
		PlayMoveSound();
	pCharContr->MoveRightDownOnGrid();
}

void MovementObserver::PlayMoveSound() const
{
	AudioServiceLocator::GetAudio()->PlaySound(0, 100);
}
