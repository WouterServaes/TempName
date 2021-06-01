#include "MiniginPCH.h"
#include "PlayerObserver.h"

#include "Events.h"
#include "GameObject.h"
#include "Health_Comp.h"
#include "Scene.h"
#include "Score_Comp.h"

#include "Text_Comp.h"
#include "Transform.h"
#include "Transform_Comp.h"

void PlayerObserver::OnNotify(GameObject* const gameObject, const Event event)
{
	switch (event)
	{
	case Event::LostLive:
		UpdateHealthUi(gameObject);
		break;
	case Event::FellOffGrid:
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
	const char* healthCompName{};

	if (std::string(gameObject->GetName()) == std::string("Player1")) //TODO fix this
		healthCompName = "Player1_HealthUi";
	else
		healthCompName = "Player2_HealthUi";

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

void PlayerObserver::HandleMove(GameObject* pGameObject)
{
	const auto pos = pGameObject->GetTransform()->GetPosition();
	pGameObject->GetTransform()->SetPosition(pos.x + 30 * Time::GetInstance().deltaTime, pos.y, pos.z);
}

void PlayerObserver::AddScore(int amount, GameObject* const playerObj)
{
	auto scoreComp{ GetScoreComponent(playerObj) };
	scoreComp->IncreaseScore(amount);
	GetScoreTextComponent(playerObj)->UpdateText(std::to_string(scoreComp->GetScore()));
}

Text_Comp* PlayerObserver::GetScoreTextComponent(const GameObject* playerObj)
{
	const char* textCompName{};
	if (std::string(playerObj->GetName()) == std::string("Player1")) //TODO fix this, i just wanted it to work for now
		textCompName = "Player1_ScoreUi";
	else
		textCompName = "Player2_ScoreUi";
	return playerObj->GetCurrentScene()->GetGameObject(textCompName)->GetComponent<Text_Comp>();
}

Score_Comp* PlayerObserver::GetScoreComponent(GameObject* const playerObj)
{
	return playerObj->GetComponent<Score_Comp>();
}