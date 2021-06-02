#include "MiniginPCH.h"
#include "LevelScene.h"

#include "CharacterController_Comp.h"
#include "EngineSettings.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MovementObserver.h"
#include "Render_Comp.h"
#include "ResourceManager.h"
#include "Subject.h"
#include "Texture2D.h"
#include "Transform.h"
#include "WorldTileManager_Comp.h"
#include "GameCommands.h"

#include "CharacterController_Comp.h"
#include "Player_Comp.h"
#include "Animation_Comp.h"
#include "CharacterObserver.h"
#include "GameController_Comp.h"
#include "GameObserver.h"
#include "Health_Comp.h"
#include "ScoreObserver.h"
#include "Score_Comp.h"
#include "Text_Comp.h"
#include "TileChanger_Comp.h"

void LevelScene::InitializeScene()
{
	InitWorld();

	//player 1
	auto pPlayerObj{ std::make_shared< GameObject>("pl", true) };
	AddGameObject(pPlayerObj);
	pPlayerObj->AddComponent(new Render_Comp());
	auto* pAnimComp{ new Animation_Comp("Images/QBert.png", 4, 8, glm::vec2(128.f, 147.f)) };
	pPlayerObj->AddComponent(pAnimComp);
	pPlayerObj->AddComponent(new CharacterController_Comp(.025f));
	pPlayerObj->AddComponent(new Player_Comp());
	pPlayerObj->AddComponent(new TileChanger_Comp());
	auto* pPl1Score{ new Score_Comp() };
	pPlayerObj->AddComponent(pPl1Score);
	auto* pPl1Health{ new Health_Comp(3, 3) };
	pPlayerObj->AddComponent(pPl1Health);
	pPlayerObj->GetSubject()->AddObserver(new MovementObserver());
	pPlayerObj->GetSubject()->AddObserver(new ScoreObserver());
	pPlayerObj->GetSubject()->AddObserver(new CharacterObserver());
	pPlayerObj->SetRenderLayer(5);
	pPlayerObj->GetTransform()->ScaleUniform(.25f);

	//player 1 lives
	const std::string font{ "Fonts/Lingua.otf" };
	auto pLiveDisplay{ std::make_shared<GameObject>("Player1LiveUi") };
	pLiveDisplay->AddComponent(new Render_Comp());
	auto* pLiveText{ new Text_Comp("Lives: ", font, 18) };
	pLiveDisplay->AddComponent(pLiveText);
	pPl1Health->AttachTextComp(pLiveText);
	AddGameObject(pLiveDisplay);
	pLiveDisplay->GetTransform()->SetPosition(30, 50);

	//player 1 score
	auto pScoreDisplay{ std::make_shared<GameObject>("Player1ScoreUi") };
	pScoreDisplay->AddComponent(new Render_Comp());
	auto* pScoreText{new Text_Comp("Score: ", font, 18)};
	pScoreDisplay->AddComponent(pScoreText);
	pPl1Score->AttachTextComp(pScoreText);
	AddGameObject(pScoreDisplay);
	pScoreDisplay->GetTransform()->SetPosition(30, 70);
	
	//game controller
	auto pGameController{ std::make_shared<GameObject>("GameController", true) };
	AddGameObject(pGameController);
	pGameController->AddComponent(new GameController_Comp());
	pGameController->GetSubject()->AddObserver(new GameObserver());

}

void LevelScene::InitUi()
{
}

void LevelScene::InitWorld()
{
	const auto pNormalTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Normal.png") }
	, pHighlightTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Highlighted.png") };

	const auto bottomRowAmount{ 7 };
	auto pWorldGridManager{ std::make_shared<GameObject>("WorldTileManager") };
	AddGameObject(pWorldGridManager);
	pWorldGridManager->GetTransform()->ScaleUniform(.5f);
	pWorldGridManager->AddComponent(new WorldTileManager_Comp(pNormalTexture, pHighlightTexture, bottomRowAmount));
}

void LevelScene::InitPlayerManager()
{
	//initializes gameObject playerManager with playerManagerComp.
	//this comp can add/remove player
	//a player is added when a GameCommand "AddPlayer" is fired, this is fired from a ui click or something

	//player has health component, qbert component, score component, animation component
}

void LevelScene::InitCoily()
{
	//has coily component
		//this component changes position of game object
}