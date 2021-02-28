#include "MiniginPCH.h"
#include "DemoScene.h"

#include "AnimationComponent.h"
#include "Commands.h"
#include "Events.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "Transform.h"
#include "UIComponent.h"
#include "HealthComponent.h"

#include "InputManager.h"
#include "PlayerObserver.h"
#include "Subject.h"
void dae::DemoScene::InitializeScene()
{
	std::string font{ "Lingua.otf" };
	auto pCurrentScene = this;
	auto gameObject = std::make_shared<GameObject>(L"Background", pCurrentScene);
	gameObject->AddComponent(new RenderComponent("background.jpg"));
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"AnimatedLogo", pCurrentScene);
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new AnimationComponent("AnimLogo", "logo_", 60, 25));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(216.f, 180.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"ProgrammingText", pCurrentScene);
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new TextComponent("Programming 4 Assignment", font, 36));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(80.f, 20.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"Fps", pCurrentScene);
	gameObject->AddComponent(new FpsUI());
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(5.f, 5.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"StartButtons", pCurrentScene);
	gameObject->AddComponent(new StartUI());
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(80.f, 200.f);
	AddGameObject(gameObject);

	const float maxHealth{ 5 };
	auto qBert = std::make_shared<GameObject>(L"QBert", pCurrentScene, true);
	qBert->AddComponent(new HealthComponent(maxHealth));
	qBert->GetSubject()->AddObserver(new PlayerObserver());
	AddGameObject(qBert);


	gameObject = std::make_shared<GameObject>(L"HealthTextUi", pCurrentScene);
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new TextComponent("Remaining lives (player 1): ", font, 22));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(5.f, 50.f);
	AddGameObject(gameObject);
	
	const auto healthText{ std::to_string(GetGameObject(L"QBert")->GetComponent<HealthComponent>()->GetLives())};
	gameObject = std::make_shared<GameObject>(L"HealthUi", pCurrentScene);
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new TextComponent(healthText, font, 22));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(300.f, 50.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"DeadText", pCurrentScene);
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new TextComponent("Player died", font, 30));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(200.f, 250.f);
	gameObject->SetActive(false);
	AddGameObject(gameObject);
	
	auto& inputManager{ InputManager::GetInstance() };
	inputManager.AssignKey(ControllerButtons::ButtonA, std::make_unique<Command_RemoveHp>(qBert));
}
void dae::DemoScene::UpdateScene()
{
	UpdatePlayerLives();
}

void dae::DemoScene::UpdatePlayerLives()
{
	auto& player = GetGameObject(L"QBert");
	auto playerHealthComp{ player->GetComponent<HealthComponent>() };
	
	if(playerHealthComp->GetHealth()<=0.f)
	{
		playerHealthComp->RemoveLives(1);
		player->GetSubject()->Notify(player, Event::LostLive);
		playerHealthComp->ResetHealth();
	}
	
	if (playerHealthComp->GetLives() <= 0)
	{
		player->GetSubject()->Notify(GetGameObject(L"DeadText"), Event::PlayerDied);
	}
}

