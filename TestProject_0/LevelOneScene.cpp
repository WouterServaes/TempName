#include "MiniginPCH.h"
#include "LevelOneScene.h"

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
#include "GameObserver.h"
#include "Health_Comp.h"
#include "ScoreObserver.h"
#include "Score_Comp.h"
#include "Text_Comp.h"
#include "TileChanger_Comp.h"

void LevelOneScene::InitializeScene()
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
	pPlayerObj->AddComponent(new Score_Comp());
	pPlayerObj->AddComponent(new Health_Comp(10.f, 10.f, 3, 3));
	pPlayerObj->GetSubject()->AddObserver(new MovementObserver());
	pPlayerObj->GetSubject()->AddObserver(new ScoreObserver());
	pPlayerObj->GetSubject()->AddObserver(new CharacterObserver());
	pPlayerObj->SetRenderLayer(5);
	pPlayerObj->GetTransform()->ScaleUniform(.25f);

	//player 1 lives
	const std::string font{ "Fonts/Lingua.otf" };
	auto pLiveDisplay{ std::make_shared<GameObject>("LiveDisplay") };
	pLiveDisplay->AddComponent(new Render_Comp());
	auto* pLiveText{ new Text_Comp("Lives: ", font, 18) };
	pLiveDisplay->AddComponent(pLiveText);
	AddGameObject(pLiveDisplay);
	pLiveDisplay->GetTransform()->SetPosition(30, 50);

	//game controller
	auto pGameController{ std::make_shared<GameObject>("GameController", true) };
	AddGameObject(pGameController);
	pGameController->GetSubject()->AddObserver(new GameObserver());
}

void LevelOneScene::InitUi()
{
}

void LevelOneScene::InitWorld()
{
	const auto pNormalTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Normal.png") }
	, pHighlightTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Highlighted.png") };

	const auto bottomRowAmount{ 7 };
	auto pWorldGridManager{ std::make_shared<GameObject>("WorldTileManager") };
	AddGameObject(pWorldGridManager);
	pWorldGridManager->GetTransform()->ScaleUniform(.5f);
	pWorldGridManager->AddComponent(new WorldTileManager_Comp(pNormalTexture, pHighlightTexture, bottomRowAmount));
}

void LevelOneScene::InitPlayerManager()
{
	//initializes gameObject playerManager with playerManagerComp.
	//this comp can add/remove player
	//a player is added when a GameCommand "AddPlayer" is fired, this is fired from a ui click or something

	//player has health component, qbert component, score component, animation component
}

void LevelOneScene::InitCoily()
{
	//has coily component
		//this component changes position of game object
}