#include "MiniginPCH.h"
#include "GameObserver.h"
#include "Events.h"
#include "GameController_Comp.h"
#include "GameObject.h"

void GameObserver::OnNotify(GameObject* pGameObject,const Event event)
{
	switch (event)
	{
	case Event::GridComplete:
		GridComplete(pGameObject);
		break;
	case Event::PlayerDied:
		PlayerDied(pGameObject);
	default:
		break;
	}
}

void GameObserver::GridComplete(GameObject* pGameObject)
{
	pGameObject->GetComponent<GameController_Comp>()->CompletedGrid();
}

void GameObserver::PlayerDied(GameObject* pGameObject)
{
	pGameObject->GetComponent<GameController_Comp>()->PlayerDied();
}
