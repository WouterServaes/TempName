#include "MiniginPCH.h"
#include "ScoreObserver.h"
#include "Events.h"
#include "GameObject.h"
#include "Score_Comp.h"

void ScoreObserver::OnNotify(GameObject* pGameObject, const Event event)
{
	switch (event)
	{
	case Event::ColorChanged:
		IncreaseScore(pGameObject, 25);
		break;
	case Event::DefeatedCoily:
		IncreaseScore(pGameObject, 500);
		break;
	case Event::DiskLeftAtEnd:
		IncreaseScore(pGameObject, 50);
		break;
	case Event::CatchedSlickOrSam:
		IncreaseScore(pGameObject, 300);
		break;
	default:;
	}
}

void ScoreObserver::IncreaseScore(GameObject* pGameObject, const int amount)
{
	pGameObject->GetComponent<Score_Comp>()->IncreaseScore(amount);
}