#include "MiniginPCH.h"

#include "QBertGame.h"



#include "AudioLogger.h"
#include "AudioServiceLocator.h"
#include "CoopScene.h"
#include "GameAudio.h"
#include "SceneManager.h"
#include "SinglePlayerScene.h"
#include "StartMenuScene.h"
#include "SceneParser.h"
#include "VersusScene.h"

void QBertGame::LoadGame()
{

	SceneParser::LoadGameFromFile("../Data/GameJsonFiles/QBert.json");
	
	AudioServiceLocator::ProvideAudioService(new AudioLogger(new GameAudio()));
	
	Logger::LogInfo("Loading game...");
	auto& sceneManager{ SceneManager::GetInstance() };
	sceneManager.AddScene(std::make_shared<StartMenuScene>("StartMenuScene"));
	sceneManager.AddScene(std::make_shared<SinglePlayerScene>("SinglePlayerScene"));
	sceneManager.AddScene(std::make_shared<CoopScene>("CoopScene"));
	sceneManager.AddScene(std::make_shared<VersusScene>("VersusScene"));
	sceneManager.LoadScene("StartMenuScene");
}
