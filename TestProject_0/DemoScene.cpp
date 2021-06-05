#include "MiniginPCH.h"

#include "DemoScene.h"
#include "Transform.h"
#include "InputManager.h"
#include "PlayerObserver.h"
#include "Subject.h"

#include "Animation_Comp.h"
#include "GameCommands.h"
#include "Render_Comp.h"
#include "Text_Comp.h"
#include "UI_Comp.h"
#include "Health_Comp.h"
#include "QBert_Comp.h"
#include "Score_Comp.h"
#include "UiComponents.h"

void DemoScene::InitializeScene()
{
	const std::string font{ "Fonts/Lingua.otf" };
	auto gameObject = std::make_shared<GameObject>("Background");
	gameObject->AddComponent(new Render_Comp("Images/background.jpg"));
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>("AnimatedLogo");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Animation_Comp("Images/AnimLogo", "logo_", 60, 25));
	gameObject->GetTransform()->SetPosition(216.f, 180.f);
	AddGameObject(gameObject);

	/*gameObject = std::make_shared<GameObject>("TestAnimation", pCurrentScene);
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Animation_Comp("Images/TestAnimSheet.png", 4, 2, glm::vec2(100, 100)));
	gameObject->GetTransform()->SetPosition(200.f, 150.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>("t", pCurrentScene);
	gameObject->AddComponent(new Render_Comp("Images/TestAnimSheet.png"));
	gameObject->GetTransform()->SetPosition(300.f, 150.f);
	AddGameObject(gameObject);*/

	gameObject = std::make_shared<GameObject>("ProgrammingText");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Programming 4 Assignment", font, 36));
	gameObject->GetTransform()->SetPosition(80.f, 20.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>("Fps");
	gameObject->AddComponent(new FpsUI());
	gameObject->GetTransform()->SetPosition(5.f, 5.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>("StartButtons");
	gameObject->AddComponent(new StartUI());
	gameObject->GetTransform()->SetPosition(80.f, 200.f);
	AddGameObject(gameObject);

	AddPlayers();
	AddUi(font);

	InitInput();
}

void DemoScene::AddPlayers()
{

	const int maxHealth{ 5 };

	auto player1 = std::make_shared<GameObject>("Player1", true);
	player1->AddComponent(new Render_Comp());
	player1->AddComponent(new Animation_Comp("Images/TestAnimSheet.png", 4, 2, glm::vec2(100, 100)));
	player1->AddComponent(new Health_Comp(maxHealth));
	player1->AddComponent(new Score_Comp());
	player1->AddComponent(new QBert_Comp());
	player1->GetSubject()->AddObserver(new PlayerObserver());
	player1->GetTransform()->SetPosition(10, 10);
	AddGameObject(player1);

	auto player2 = std::make_shared<GameObject>("Player2", true);
	player2->AddComponent(new Health_Comp(maxHealth));
	player2->AddComponent(new Score_Comp());
	player2->AddComponent(new QBert_Comp());
	player2->GetSubject()->AddObserver(new PlayerObserver());
	AddGameObject(player2);
}

void DemoScene::AddUi(const std::string& font)
{
	//health
	auto gameObject = std::make_shared<GameObject>("Player1_HealthTextUi");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Remaining lives (player 1): ", font, 22));
	gameObject->GetTransform()->SetPosition(5.f, 50.f);
	AddGameObject(gameObject);

	auto healthText{ std::to_string(GetGameObject("Player1")->GetComponent<Health_Comp>()->GetLives()) };
	gameObject = std::make_shared<GameObject>("Player1_HealthUi");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp(healthText, font, 22));
	gameObject->AddComponent(new Score_Comp());
	gameObject->GetTransform()->SetPosition(300.f, 50.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>("Player2_HealthTextUi");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Remaining lives (player 2): ", font, 22));
	gameObject->GetTransform()->SetPosition(5.f, 100.f);
	AddGameObject(gameObject);

	healthText = std::to_string(GetGameObject("Player2")->GetComponent<Health_Comp>()->GetLives());
	gameObject = std::make_shared<GameObject>("Player2_HealthUi");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp(healthText, font, 22));
	gameObject->AddComponent(new Score_Comp());
	gameObject->GetTransform()->SetPosition(300.f, 100.f);
	AddGameObject(gameObject);

	//score
	gameObject = std::make_shared<GameObject>("Player1_ScoreTextUi");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Score (player 1): ", font, 22));
	gameObject->GetTransform()->SetPosition(400.f, 50.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>("Player2_ScoreTextUi");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Score (player 2): ", font, 22));
	gameObject->GetTransform()->SetPosition(400.f, 100.f);
	AddGameObject(gameObject);

	auto scoreText{ std::to_string(GetGameObject("Player1")->GetComponent<Score_Comp>()->GetScore()) };
	gameObject = std::make_shared<GameObject>("Player1_ScoreUi");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp(scoreText, font, 22));
	gameObject->GetTransform()->SetPosition(600.f, 50.f);
	AddGameObject(gameObject);

	scoreText = std::to_string(GetGameObject("Player2")->GetComponent<Score_Comp>()->GetScore());
	gameObject = std::make_shared<GameObject>("Player2_ScoreUi");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp(scoreText, font, 22));
	gameObject->GetTransform()->SetPosition(600.f, 100.f);
	AddGameObject(gameObject);

	//dead
	gameObject = std::make_shared<GameObject>("DeadText");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Player died", font, 30));
	gameObject->GetTransform()->SetPosition(200.f, 250.f);
	gameObject->SetActive(false);
	AddGameObject(gameObject);

	//controls
	gameObject = std::make_shared<GameObject>("Player1_ControlsText");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Player 1: A: remove hp - B: Catch Slick/Sam - X: Color change - Y: defeat Coily ", font, 15));
	gameObject->GetTransform()->SetPosition(10.f, 300.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>("Player2_ControlsText");
	gameObject->AddComponent(new Render_Comp());
	gameObject->AddComponent(new Text_Comp("Player 2: Down: remove hp - Right: Catch Slick/Sam - Left: Color change - Up: defeat Coily ", font, 15));
	gameObject->GetTransform()->SetPosition(10.f, 325.f);
	AddGameObject(gameObject);
}

void DemoScene::InitInput()
{
	GameObject* player1{ GetGameObject("Player1").get() };
	GameObject* player2{ GetGameObject("Player2").get() };

	auto& inputManager{ InputManager::GetInstance() };
	inputManager.SetMaxControllerAmount(2);

	InputAction inputAction{ InputAction('w', TriggerState::Released, ControllerButtons::ButtonA, 0) };
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



	//move test
	//inputAction = InputAction('z', TriggerState::Down, ControllerButtons::ButtonB, 0);
	//inputManager.AssignKey(inputAction, std::make_unique<Command_MoveLeftUp>(player1));
}