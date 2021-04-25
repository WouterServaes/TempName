#include "MiniginPCH.h"

#include "TestGame.h"

#include "DemoScene.h"
#include "SceneManager.h"

void TestGame::LoadGame()
{
		Logger::LogInfo("Loading game...");
	auto& sceneManager{dae::SceneManager::GetInstance() };
	sceneManager.AddScene(std::make_shared<dae::DemoScene>("Demo"));	
}
