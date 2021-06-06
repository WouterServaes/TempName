#include "MiniginPCH.h"
#include "StartMenuScene.h"



#include "AudioServiceLocator.h"
#include "EngineSettings.h"
#include "Minigin.h"
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

}

void StartMenuScene::InitAudio()
{
	auto* audio{ AudioServiceLocator::GetAudio() };

	audio->AddAudioFile("../Data/Audio/Jump.wav");
	audio->AddAudioFile("../Data/Audio/Fall.wav");
	audio->AddAudioFile("../Data/Audio/SnakeFall.wav");
	audio->AddAudioFile("../Data/Audio/Victory.wav");
}
