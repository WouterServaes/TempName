#include "MiniginPCH.h"
#include "CharacterObserver.h"

#include "CharacterController_Comp.h"
#include "Events.h"
#include "GameObject.h"
#include "Health_Comp.h"

void CharacterObserver::OnNotify(GameObject* pGameObject, const Event event)
{
	switch (event)
	{
	case Event::FellOffGrid:
		FellOffGrid(pGameObject);
		break;
	default: ;
	}
}

void CharacterObserver::FellOffGrid(GameObject* pGameObject)
{
	pGameObject->GetComponent<CharacterController_Comp>()->GoToSpawnPos();

	auto* pHealthComp{ pGameObject->GetComponent<Health_Comp>() };
	if (pHealthComp) pHealthComp->RemoveLives();
}
