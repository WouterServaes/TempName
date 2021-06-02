#include "MiniginPCH.h"
#include "GreenCreatureObserver.h"
#include "Events.h"
#include "GameObject.h"
#include "GreenCreature_Comp.h"

void GreenCreatureObserver::OnNotify(GameObject* pGameObject,const Event event)
{
	switch (event)
	{
	case Event::FellOffGrid:
		FellOffGrid(pGameObject);
		break;
	default: ;
	}
}

void GreenCreatureObserver::FellOffGrid(GameObject* pGameObject)
{
	pGameObject->GetComponent<GreenCreature_Comp>()->Respawn();
}
