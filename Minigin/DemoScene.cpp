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
#include "ScoreComponent.h"
#include "Subject.h"
void dae::DemoScene::InitializeScene()
{
	const std::string font{ "Lingua.otf" };
	auto *pCurrentScene = this;
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

	AddPlayers();
	AddUi(font);

	
	auto& player1{ GetGameObject(L"Player1") };
	auto& player2{ GetGameObject(L"Player2") };
	
	auto& inputManager{ InputManager::GetInstance() };
	inputManager.AssignKey(ControllerButtons::ButtonA, std::make_unique<Command_RemoveHp>(player1));
	inputManager.AssignKey(ControllerButtons::ButtonB, std::make_unique<Command_CatchedSlickOrSam>(player1));
	inputManager.AssignKey(ControllerButtons::ButtonX, std::make_unique<Command_ColorChanged>(player1));
	inputManager.AssignKey(ControllerButtons::ButtonY, std::make_unique<Command_DefeatedCoily>(player1));


	inputManager.AssignKey(ControllerButtons::ButtonDown, std::make_unique<Command_RemoveHp>(player2));
	inputManager.AssignKey(ControllerButtons::ButtonRight, std::make_unique<Command_CatchedSlickOrSam>(player2));
	inputManager.AssignKey(ControllerButtons::ButtonLeft, std::make_unique<Command_ColorChanged>(player2));
	inputManager.AssignKey(ControllerButtons::ButtonDown, std::make_unique<Command_DefeatedCoily>(player2));
}

void dae::DemoScene::AddPlayers()
{
	auto *pCurrentScene = this;
	
	const float maxHealth{ 5 };
	
	auto player1 = std::make_shared<GameObject>(L"Player1", pCurrentScene, true);
	player1->AddComponent(new HealthComponent(maxHealth));
	player1->AddComponent(new ScoreComponent());
	player1->GetSubject()->AddObserver(new PlayerObserver());
	AddGameObject(player1);



	auto player2 = std::make_shared<GameObject>(L"Player2", pCurrentScene, true);
	player2->AddComponent(new HealthComponent(maxHealth));
	player2->AddComponent(new ScoreComponent());
	player2->GetSubject()->AddObserver(new PlayerObserver());
	AddGameObject(player2);
}

void dae::DemoScene::AddUi(const std::string& font)
{	
	auto *pCurrentScene = this;
	auto gameObject = std::make_shared<GameObject>(L"Player1_HealthTextUiO", pCurrentScene);
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new TextComponent("Remaining lives (player 1): ", font, 22));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(5.f, 50.f);
	AddGameObject(gameObject);

	auto healthText{ std::to_string(GetGameObject(L"Player1")->GetComponent<HealthComponent>()->GetLives()) };
	gameObject = std::make_shared<GameObject>(L"Player1_HealthUi", pCurrentScene);
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new TextComponent(healthText, font, 22));
	gameObject->AddComponent(new ScoreComponent());
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(300.f, 50.f);
	AddGameObject(gameObject);


	gameObject = std::make_shared<GameObject>(L"Player2_HealthTextUiO", pCurrentScene);
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new TextComponent("Remaining lives (player 2): ", font, 22));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(5.f, 100.f);
	AddGameObject(gameObject);

	healthText = std::to_string(GetGameObject(L"Player2")->GetComponent<HealthComponent>()->GetLives()) ;
	gameObject = std::make_shared<GameObject>(L"Player2_HealthUi", pCurrentScene);
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new TextComponent(healthText, font, 22));
	gameObject->AddComponent(new ScoreComponent());
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(300.f, 100.f);
	AddGameObject(gameObject);

	
	gameObject = std::make_shared<GameObject>(L"DeadText", pCurrentScene);
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new TextComponent("Player died", font, 30));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(200.f, 250.f);
	gameObject->SetActive(false);
	AddGameObject(gameObject);
}

void dae::DemoScene::UpdateScene()
{
	UpdatePlayer1Lives();
	UpdatePlayer2Lives();
}


void dae::DemoScene::UpdatePlayer1Lives()
{
	auto& player1{ GetGameObject(L"Player1") };
	

	auto playerHealthComp{ player1->GetComponent<HealthComponent>() };
	if (playerHealthComp->GetHealth() <= 0.f)
	{
		playerHealthComp->RemoveLives(1);
		player1->GetSubject()->Notify(player1, Event::LostLive);
		playerHealthComp->ResetHealth();
	}

	if (playerHealthComp->GetLives() <= 0)
	{
		player1->GetSubject()->Notify(GetGameObject(L"DeadText"), Event::PlayerDied);
	}
}

void dae::DemoScene::UpdatePlayer2Lives()
{
	auto& player2{ GetGameObject(L"Player2") };
	auto playerHealthComp {player2->GetComponent<HealthComponent>()};
	if (playerHealthComp->GetHealth() <= 0.f)
	{
		playerHealthComp->RemoveLives(1);
		player2->GetSubject()->Notify(player2, Event::LostLive);
		playerHealthComp->ResetHealth();
	}

	if (playerHealthComp->GetLives() <= 0)
	{
		player2->GetSubject()->Notify(GetGameObject(L"DeadText"), Event::PlayerDied);
	}
}



