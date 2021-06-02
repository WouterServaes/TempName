#include "MiniginPCH.h"

#include "TestGame.h"

#include "SceneManager.h"
#include "LevelScene.h"
void TestGame::LoadGame()
{
	Logger::LogInfo("Loading game...");
	auto& sceneManager{ SceneManager::GetInstance() };
	//sceneManager.AddScene(std::make_shared<DemoScene>("Demo"));
	sceneManager.AddScene(std::make_shared<LevelScene>("Level"));
}