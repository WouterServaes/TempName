#include "MiniginPCH.h"

#include "TestGame.h"



#include "AudioLogger.h"
#include "AudioServiceLocator.h"
#include "GameAudio.h"
#include "SceneManager.h"
#include "LevelScene.h"
#include "StartMenuScene.h"

void TestGame::LoadGame()
{
	AudioServiceLocator::ProvideAudioService(new AudioLogger(new GameAudio()));
	
	Logger::LogInfo("Loading game...");
	auto& sceneManager{ SceneManager::GetInstance() };
	//sceneManager.AddScene(std::make_shared<DemoScene>("Demo"));
	sceneManager.AddScene(std::make_shared<StartMenuScene>("StartMenuScene"));
	sceneManager.AddScene(std::make_shared<LevelScene>("Level"));
	sceneManager.LoadScene("StartMenuScene");
}
