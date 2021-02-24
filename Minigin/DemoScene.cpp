#include "MiniginPCH.h"
#include "DemoScene.h"

#include "AnimationComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "Transform.h"
#include "UIComponent.h"

void dae::DemoScene::InitializeScene()
{
	auto gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new RenderComponent("background.jpg"));
	Add(gameObject);

	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new AnimationComponent("AnimLogo", "logo_", 60, 25));
	gameObject->GetComponent<TransformComponent>()->GetTransform()->SetPosition(216.f, 180.f);
	Add(gameObject);

	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new RenderComponent());
	gameObject->AddComponent(new TextComponent("Programming 4 Assignment", "Lingua.otf", 36));
	gameObject->GetComponent<TransformComponent>()->GetTransform()->SetPosition(80.f, 20.f);
	Add(gameObject);

	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new FpsUI());
	gameObject->GetComponent<TransformComponent>()->GetTransform()->SetPosition(5.f, 5.f);
	Add(gameObject);

	gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent(new StartUI());
	gameObject->GetComponent<TransformComponent>()->GetTransform()->SetPosition(80.f, 200.f);
	Add(gameObject);
}