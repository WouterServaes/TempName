#include "MiniginPCH.h"
#include "PlayerObserver.h"

#include "Events.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "Scene.h"
#include "ScoreComponent.h"

#include "TextComponent.h"

void dae::PlayerObserver::OnNotify(const std::shared_ptr<GameObject>& gameObject, Event event)
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

void dae::PlayerObserver::UpdateHealthUi(const std::shared_ptr<GameObject>& gameObject)
{
	const wchar_t* healthCompName{};
	
	if (std::wstring(gameObject->GetName()) == std::wstring(L"Player1"))  //TODO fix this
		healthCompName = L"Player1_HealthUi";
	else
		healthCompName = L"Player2_HealthUi";

	auto* pHealthUi{gameObject->GetCurrentScene()->GetGameObject(healthCompName)->GetComponent<TextComponent>()};
	const auto currentHealth{ gameObject->GetConstComponent<HealthComponent>()->GetLives() };

	pHealthUi->UpdateText(std::to_string(currentHealth));	
}

void dae::PlayerObserver::ShowPlayerDied(const std::shared_ptr<GameObject>& gameObject)
{
	gameObject->SetActive(true);
}

void dae::PlayerObserver::HandleCatchedSlickOrSame(const std::shared_ptr<GameObject>& gameObject)
{
	gameObject->GetComponent<ScoreComponent>()->IncreaseScore(300);
}

void dae::PlayerObserver::HandleColorChanged(const std::shared_ptr<GameObject>& gameObject)
{
	gameObject->GetComponent<ScoreComponent>()->IncreaseScore(25);
}
void dae::PlayerObserver::HandleDefeatedCoily(const std::shared_ptr<GameObject>& gameObject)
{
	gameObject->GetComponent<ScoreComponent>()->IncreaseScore(500);
}

void dae::PlayerObserver::HandleLeftDiskAtEnd(const std::shared_ptr<GameObject>& gameObject)
{
	gameObject->GetComponent<ScoreComponent>()->IncreaseScore(50);
}