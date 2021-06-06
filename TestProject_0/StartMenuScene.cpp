#include "MiniginPCH.h"
#include "StartMenuScene.h"



#include "AudioServiceLocator.h"
#include "EngineSettings.h"
#include "Minigin.h"
#include "SceneParser.h"
#include "Text_Comp.h"
#include "Transform.h"
#include "UiComponents.h"

void StartMenuScene::InitializeScene()
{
	InitAudio();
	auto menuText{ std::make_shared<GameObject>("menuText") };
	menuText->AddComponent(new StartUI());
	AddGameObject(menuText);

	auto settings{ Minigin::pEngineSettings };
	menuText->GetTransform()->SetPosition(settings->WindowWidth / 2.f - 50.f, settings->WindowHeight / 2.f);

	const auto sceneData{ SceneParser::GetSceneData(0) };
	const std::string font{ sceneData->Font };
	const auto fontColor{ sceneData->FontColor };
	auto pTitle{ std::make_shared<GameObject>("GameOver") };
	pTitle->AddComponent(new Render_Comp());
	pTitle->AddComponent(new Text_Comp("QBert!", font, 28, fontColor));
	pTitle->GetTransform()->SetPosition(220.f, 150.f);
	AddGameObject(pTitle);
	
}

void StartMenuScene::InitAudio()
{
	auto* audio{ AudioServiceLocator::GetAudio() };

	audio->AddAudioFile("../Data/Audio/Jump.wav");
	audio->AddAudioFile("../Data/Audio/Fall.wav");
	audio->AddAudioFile("../Data/Audio/SnakeFall.wav");
	audio->AddAudioFile("../Data/Audio/Victory.wav");
}
