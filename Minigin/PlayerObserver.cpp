#include "MiniginPCH.h"
#include "PlayerObserver.h"

#include "Events.h"
#include "GameObject.h"
#include "Health_Comp.h"
#include "Scene.h"
#include "Score_Comp.h"

#include "Text_Comp.h"

void PlayerObserver::OnNotify(GameObject* const gameObject, Event event)
{
	switch (event)
	{
	case Event::LostLive:
		UpdateHealthUi(gameObject);
		break;
	case Event::PlayerDied:
		ShowPlayerDied(gameObject);
		break;

	case Event::DefeatedCoily:
		HandleDefeatedCoily(gameObject);
		break;
	case Event::CatchedSlickOrSam:
		HandleCatchedSlickOrSame(gameObject);
		break;
	case Event::ColorChanged:
		HandleColorChanged(gameObject);
		break;
	case Event::DiskLeftAtEnd:
		HandleLeftDiskAtEnd(gameObject);
		break;
	}
}

void PlayerObserver::UpdateHealthUi(const GameObject* gameObject)
{
	const wchar_t* healthCompName{};

	if (std::wstring(gameObject->GetName()) == std::wstring(L"Player1")) //TODO fix this
		healthCompName = L"Player1_HealthUi";
	else
		healthCompName = L"Player2_HealthUi";

	auto* pHealthUi{ gameObject->GetCurrentScene()->GetGameObject(healthCompName)->GetComponent<Text_Comp>() };
	const auto currentHealth{ gameObject->GetConstComponent<Health_Comp>()->GetLives() };

	pHealthUi->UpdateText(std::to_string(currentHealth));
}

void PlayerObserver::ShowPlayerDied(GameObject* const gameObject)
{
	gameObject->SetActive(true);
}

void PlayerObserver::HandleCatchedSlickOrSame(GameObject* const gameObject)
{
	AddScore(300, gameObject);
}

void PlayerObserver::HandleColorChanged(GameObject* const gameObject)
{
	AddScore(25, gameObject);
}
void PlayerObserver::HandleDefeatedCoily(GameObject* const gameObject)
{
	AddScore(500, gameObject);
}

void PlayerObserver::HandleLeftDiskAtEnd(GameObject* const gameObject)
{
	AddScore(50, gameObject);
}

void PlayerObserver::AddScore(int amount, GameObject* const playerObj)
{
	auto scoreComp{ GetScoreComponent(playerObj) };
	scoreComp->IncreaseScore(amount);
	GetScoreTextComponent(playerObj)->UpdateText(std::to_string(scoreComp->GetScore()));
}

Text_Comp* PlayerObserver::GetScoreTextComponent(const GameObject* playerObj)
{
	const wchar_t* textCompName{};
	if (std::wstring(playerObj->GetName()) == std::wstring(L"Player1")) //TODO fix this, i just wanted it to work for now
		textCompName = L"Player1_ScoreUi";
	else
		textCompName = L"Player2_ScoreUi";
	return playerObj->GetCurrentScene()->GetGameObject(textCompName)->GetComponent<Text_Comp>();
}

Score_Comp* PlayerObserver::GetScoreComponent(GameObject* const playerObj)
{
	return playerObj->GetComponent<Score_Comp>();
}