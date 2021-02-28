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
	AddScore(300, gameObject);
}

void dae::PlayerObserver::HandleColorChanged(const std::shared_ptr<GameObject>& gameObject)
{
	AddScore(25, gameObject);
}
void dae::PlayerObserver::HandleDefeatedCoily(const std::shared_ptr<GameObject>& gameObject)
{
	AddScore(500, gameObject);
}

void dae::PlayerObserver::HandleLeftDiskAtEnd(const std::shared_ptr<GameObject>& gameObject)
{
	AddScore(50, gameObject);
}

void dae::PlayerObserver::AddScore(int amount, const std::shared_ptr<GameObject>& playerObj)
{
	auto scoreComp{ GetScoreComponent(playerObj) };
	scoreComp->IncreaseScore(amount);
	GetScoreTextComponent(playerObj)->UpdateText(std::to_string(scoreComp->GetScore()));
}

dae::TextComponent* dae::PlayerObserver::GetScoreTextComponent(const std::shared_ptr<GameObject>& playerObj)
{
	const wchar_t* textCompName{};
	if (std::wstring(playerObj->GetName()) == std::wstring(L"Player1"))  //TODO fix this, i just wanted it to work for now
		textCompName = L"Player1_ScoreUi";
	else
		textCompName = L"Player2_ScoreUi";
	return playerObj->GetCurrentScene()->GetGameObject(textCompName)->GetComponent<TextComponent>();
}

dae::ScoreComponent* dae::PlayerObserver::GetScoreComponent(const std::shared_ptr<GameObject>& playerObj)
{
	return playerObj->GetComponent<ScoreComponent>();
}
