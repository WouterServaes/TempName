#include "MiniginPCH.h"
#include "CreatureObserver.h"
#include "Events.h"
#include "GameObject.h"
#include "Creature_Comp.h"
#include "PurpleCreature_Comp.h"
#include "GreenCreature_Comp.h"
#include "CoilyCreature_Comp.h"

void CreatureObserver::OnNotify(GameObject* pGameObject, const Event event)
{
	switch (event)
	{
	case Event::FellOffGrid:
		FellOffGrid(pGameObject);
		break;
	default:;
	}
}

void CreatureObserver::FellOffGrid(GameObject* pGameObject)
{
	PurpleCreature_Comp* pPurple{ nullptr };
	GreenCreature_Comp* pGreen{ nullptr };
	CoilyCreature_Comp* pCoily{ nullptr };
	if (pGameObject->TryGetComponent(pPurple))
		pPurple->Respawn();
	else if (pGameObject->TryGetComponent(pGreen))
		pGreen->Respawn();
	else if (pGameObject->TryGetComponent(pCoily))
		pCoily->Respawn();
}