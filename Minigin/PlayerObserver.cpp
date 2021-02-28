#include "MiniginPCH.h"
#include "PlayerObserver.h"

#include "Events.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "Scene.h"

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
	}
}

void dae::PlayerObserver::UpdateHealthUi(const std::shared_ptr<GameObject>& gameObject)
{
	auto* pHealthUi{gameObject->GetCurrentScene()->GetGameObject(L"HealthUi")->GetComponent<TextComponent>()};
	const auto currentHealth{ gameObject->GetConstComponent<HealthComponent>()->GetLives() };

	
	pHealthUi->UpdateText(std::to_string(currentHealth));
	
}

void dae::PlayerObserver::ShowPlayerDied(const std::shared_ptr<GameObject>& gameObject)
{
	
	gameObject->SetActive(true);
}
