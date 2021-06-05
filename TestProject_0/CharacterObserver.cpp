#include "MiniginPCH.h"
#include "CharacterObserver.h"

#include "CharacterController_Comp.h"
#include "Events.h"
#include "GameObject.h"
#include "Health_Comp.h"
#include "Player_Comp.h"

void CharacterObserver::OnNotify(GameObject* pGameObject, const Event event)
{
	switch (event)
	{
	case Event::FellOffGrid:
		FellOffGrid(pGameObject);
		break;
		
	case Event::AttackedByPurple:
		AttackedByPurple(pGameObject);
		break;
	default: ;
	}
}

void CharacterObserver::FellOffGrid(GameObject* pGameObject)
{
	pGameObject->GetComponent<CharacterController_Comp>()->GoToSpawnPos();

	Player_Comp* pPlayerComp{ nullptr };
	if(pGameObject->TryGetComponent(pPlayerComp))
		pPlayerComp->FellOffPyramid();
}

void CharacterObserver::AttackedByPurple(GameObject* pGameObject)
{
	pGameObject->GetComponent<CharacterController_Comp>()->GoToSpawnPos();
	Health_Comp* pHealthComp{ nullptr };
	if (pGameObject->TryGetComponent(pHealthComp))
		pHealthComp->RemoveLives();
}
