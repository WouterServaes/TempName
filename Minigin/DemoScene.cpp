#include "MiniginPCH.h"
#include "DemoScene.h"
#include "Animation_Comp.h"
#include "Commands.h"
#include "Render_Comp.h"
#include "Text_Comp.h"
#include "Transform_Comp.h"
#include "Transform.h"
#include "UI_Comp.h"
#include "Health_Comp.h"
#include "QBert_Comp.h"
#include "InputManager.h"
#include "PlayerObserver.h"
#include "Score_Comp.h"
#include "Subject.h"

void dae::DemoScene::InitializeScene()
{
	const std::string font{ "Lingua.otf" };
	auto* pCurrentScene = this;
	auto gameObject = std::make_shared<GameObject>(L"Background", pCurrentScene);
	gameObject->AddComponent(new Render_Comp("background.jpg"));
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"AnimatedLogo", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Animation_Comp("AnimLogo", "logo_", 60, 25));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(216.f, 180.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"ProgrammingText", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Programming 4 Assignment", font, 36));
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

	InitInput();
}

void dae::DemoScene::AddPlayers()
{
	auto* pCurrentScene = this;

	const float maxHealth{ 5 };

	auto player1 = std::make_shared<GameObject>(L"Player1", pCurrentScene, true);
	player1->AddComponent(new Health_Comp(maxHealth));
	player1->AddComponent(new Score_Comp());
	player1->AddComponent(new QBert_Comp());
	player1->GetSubject()->AddObserver(new PlayerObserver());
	AddGameObject(player1);

	auto player2 = std::make_shared<GameObject>(L"Player2", pCurrentScene, true);
	player2->AddComponent(new Health_Comp(maxHealth));
	player2->AddComponent(new Score_Comp());
	player2->AddComponent(new QBert_Comp());
	player2->GetSubject()->AddObserver(new PlayerObserver());
	AddGameObject(player2);

	
}

void dae::DemoScene::AddUi(const std::string& font)
{
	auto* pCurrentScene = this;
	//health
	auto gameObject = std::make_shared<GameObject>(L"Player1_HealthTextUi", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Remaining lives (player 1): ", font, 22));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(5.f, 50.f);
	AddGameObject(gameObject);

	auto healthText{ std::to_string(GetGameObject(L"Player1")->GetComponent<Health_Comp>()->GetLives()) };
	gameObject = std::make_shared<GameObject>(L"Player1_HealthUi", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp(healthText, font, 22));
	gameObject->AddComponent(new Score_Comp());
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(300.f, 50.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"Player2_HealthTextUi", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Remaining lives (player 2): ", font, 22));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(5.f, 100.f);
	AddGameObject(gameObject);

	healthText = std::to_string(GetGameObject(L"Player2")->GetComponent<Health_Comp>()->GetLives());
	gameObject = std::make_shared<GameObject>(L"Player2_HealthUi", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp(healthText, font, 22));
	gameObject->AddComponent(new Score_Comp());
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(300.f, 100.f);
	AddGameObject(gameObject);

	//score
	gameObject = std::make_shared<GameObject>(L"Player1_ScoreTextUi", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Score (player 1): ", font, 22));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(400.f, 50.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"Player2_ScoreTextUi", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Score (player 2): ", font, 22));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(400.f, 100.f);
	AddGameObject(gameObject);

	auto scoreText{ std::to_string(GetGameObject(L"Player1")->GetComponent<Score_Comp>()->GetScore()) };
	gameObject = std::make_shared<GameObject>(L"Player1_ScoreUi", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp(scoreText, font, 22));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(600.f, 50.f);
	AddGameObject(gameObject);

	scoreText = std::to_string(GetGameObject(L"Player2")->GetComponent<Score_Comp>()->GetScore());
	gameObject = std::make_shared<GameObject>(L"Player2_ScoreUi", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp(scoreText, font, 22));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(600.f, 100.f);
	AddGameObject(gameObject);

	//dead 
	gameObject = std::make_shared<GameObject>(L"DeadText", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Player died", font, 30));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(200.f, 250.f);
	gameObject->SetActive(false);
	AddGameObject(gameObject);

	//controls
	gameObject = std::make_shared<GameObject>(L"Player1_ControlsText", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Player 1:  A: remove hp - B: Catch Slick/Sam - X: Color change - Y: defeat Coily ", font, 15));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(10.f, 300.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"Player2_ControlsText", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Player 2:  Down: remove hp - Right: Catch Slick/Sam - Left: Color change - Up: defeat Coily ", font, 15));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(10.f, 325.f);
	AddGameObject(gameObject);
}

void dae::DemoScene::InitInput()
{
	GameObject* player1{ GetGameObject(L"Player1").get() };
	GameObject* player2{ GetGameObject(L"Player2").get() };

	auto& inputManager{ InputManager::GetInstance() };
	inputManager.SetMaxControllerAmount(2);

	InputAction inputAction{ InputAction('w', TriggerState::Released, ControllerButtons::ButtonA, 0)};
	inputManager.AssignKey(inputAction, std::make_unique<Command_RemoveHp>(player1));
	
	inputAction = InputAction('a', TriggerState::Released, ControllerButtons::ButtonB, 0);
	inputManager.AssignKey(inputAction, std::make_unique<Command_CatchedSlickOrSam>(player1));
	
	inputAction = InputAction('s', TriggerState::Released, ControllerButtons::ButtonX, 0);
	inputManager.AssignKey(inputAction, std::make_unique<Command_ColorChanged>(player1));
	
	inputAction = InputAction('d', TriggerState::Released, ControllerButtons::ButtonY, 0);
	inputManager.AssignKey(inputAction, std::make_unique<Command_DefeatedCoily>(player1));

	
	inputAction = InputAction(SDLK_UP, TriggerState::Released, ControllerButtons::ButtonDown, 1);
	inputManager.AssignKey(inputAction, std::make_unique<Command_RemoveHp>(player2));
	
	inputAction = InputAction(SDLK_DOWN, TriggerState::Released, ControllerButtons::ButtonRight, 1);
	inputManager.AssignKey(inputAction, std::make_unique<Command_CatchedSlickOrSam>(player2));
	
	inputAction = InputAction(SDLK_LEFT, TriggerState::Released, ControllerButtons::ButtonLeft, 1);
	inputManager.AssignKey(inputAction, std::make_unique<Command_ColorChanged>(player2));
	
	inputAction = InputAction(SDLK_RIGHT, TriggerState::Released, ControllerButtons::ButtonUp, 1);
	inputManager.AssignKey(inputAction, std::make_unique<Command_DefeatedCoily>(player2));

}
