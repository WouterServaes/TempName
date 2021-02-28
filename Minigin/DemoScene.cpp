#include "MiniginPCH.h"
#include "DemoScene.h"

#include "AnimationComponent.h"
#include "Commands.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "Transform.h"
#include "UIComponent.h"
#include "HealthComponent.h"

#include "InputManager.h"

void dae::DemoScene::InitializeScene()
{
	auto gameObject = std::make_shared<GameObject>(L"Background");
	gameObject->AddComponent(new RenderComponent("background.jpg"));
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"AnimatedLogo");
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new AnimationComponent("AnimLogo", "logo_", 60, 25));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(216.f, 180.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"ProgrammingText");
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new TextComponent("Programming 4 Assignment", "Lingua.otf", 36));
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(80.f, 20.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"Fps");
	gameObject->AddComponent(new FpsUI());
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(5.f, 5.f);
	AddGameObject(gameObject);

	gameObject = std::make_shared<GameObject>(L"StartButtons");
	gameObject->AddComponent(new StartUI());
	gameObject->GetTransformComponent()->GetTransform()->SetPosition(80.f, 200.f);
	AddGameObject(gameObject);

	auto qBert = std::make_shared<GameObject>(L"QBert");
	qBert->AddComponent(new HealthComponent());
	AddGameObject(qBert);

	auto& inputManager{ InputManager::GetInstance() };
	inputManager.AssignKey(KeyboardButtons::Space, std::make_unique<Command_RemoveHp>(qBert));
}
