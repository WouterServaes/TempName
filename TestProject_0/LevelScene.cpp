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
#include "Transform.h"
#include "WorldTileManager_Comp.h"

#include "Player_Comp.h"
#include "Animation_Comp.h"
#include "CharacterObserver.h"
#include "CoilyCreature_Comp.h"
#include "CreatureObserver.h"
#include "DiskManager_Comp.h"
#include "FloatingDisk_Comp.h"
#include "GameController_Comp.h"
#include "Health_Comp.h"
#include "GreenCreature_Comp.h"
#include "PurpleCreature_Comp.h"
#include "ScoreObserver.h"
#include "Score_Comp.h"
#include "Text_Comp.h"
#include "TileChanger_Comp.h"
#include "UI_Comp.h"

void LevelScene::InitializeScene()
{
	auto fpsCounter = std::make_shared<GameObject>("Fps");
	fpsCounter->AddComponent(new FpsUI());
	fpsCounter->GetTransform()->SetPosition(5.f, 5.f);
	AddGameObject(fpsCounter);
	
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
	auto pGameController{ std::make_shared<GameObject>("GameController") };
	AddGameObject(pGameController);
	pGameController->AddComponent(new GameController_Comp());

	//green creatures
	auto pSlick{ std::make_shared<GameObject>("Slick", true) };
	AddGameObject(pSlick);
	pSlick->AddComponent(new Render_Comp());
	pSlick->AddComponent(new Animation_Comp("Images/Slick_Sam.png", 4, 8, glm::vec2(128.f, 147.f)));
	pSlick->AddComponent(new CharacterController_Comp(.15f));
	pSlick->AddComponent(new GreenCreature_Comp(2.f));
	pSlick->AddComponent(new TileChanger_Comp(TileChanger_Comp::TileChangeLevel::RevertChanges));
	pSlick->GetTransform()->ScaleUniform(.25f);
	pSlick->GetSubject()->AddObserver(new CreatureObserver());

	auto pSam{ std::make_shared<GameObject>("Sam", true) };
	AddGameObject(pSam);
	pSam->AddComponent(new Render_Comp());
	pSam->AddComponent(new Animation_Comp("Images/Slick_Sam.png", 4, 8, glm::vec2(128.f, 147.f)));
	pSam->AddComponent(new CharacterController_Comp(.15f));
	pSam->AddComponent(new GreenCreature_Comp(2.f));
	pSam->AddComponent(new TileChanger_Comp(TileChanger_Comp::TileChangeLevel::RevertChanges));
	pSam->GetTransform()->ScaleUniform(.25f);
	pSam->GetSubject()->AddObserver(new CreatureObserver());

	////purple creatures
	//auto pUgg{ std::make_shared<GameObject>("Ugg", true) };
	//AddGameObject(pUgg);
	//pUgg->AddComponent(new Render_Comp());
	//pUgg->AddComponent(new Animation_Comp("Images/Ugg_Wrongway.png", 4, 8, glm::vec2(128.f, 147.f)));
	//pUgg->AddComponent(new CharacterController_Comp(.15f));
	//pUgg->AddComponent(new PurpleCreature_Comp(Transform::Side::Left, 2.f));
	//pUgg->GetTransform()->ScaleUniform(.25f);
	//pUgg->GetSubject()->AddObserver(new CreatureObserver());

	//auto pWrongway{ std::make_shared<GameObject>("Wrongway", true) };
	//AddGameObject(pWrongway);
	//pWrongway->AddComponent(new Render_Comp());
	//pWrongway->AddComponent(new Animation_Comp("Images/Ugg_Wrongway.png", 4, 8, glm::vec2(128.f, 147.f)));
	//pWrongway->AddComponent(new CharacterController_Comp(.15f));
	//pWrongway->AddComponent(new PurpleCreature_Comp(Transform::Side::Right, 2.f));
	//pWrongway->GetTransform()->ScaleUniform(.25f);
	//pWrongway->GetSubject()->AddObserver(new CreatureObserver());

	////coily
	//auto pCoily{ std::make_shared<GameObject>("Coily", true) };
	//AddGameObject(pCoily);
	//pCoily->AddComponent(new Render_Comp());
	//pCoily->AddComponent(new Animation_Comp("Images/CoilyEgg.png", 4, 8, glm::vec2(128.f, 147.f)));
	//pCoily->AddComponent(new CharacterController_Comp(.15f));
	//pCoily->AddComponent(new CoilyCreature_Comp(2.f, "Images/Coily.png", 4,8, glm::vec2(50.f, 147.f)));
	//pCoily->GetTransform()->ScaleUniform(.1f);
	//pCoily->GetSubject()->AddObserver(new CreatureObserver());


	////disks
	//auto pDiskManager{ std::make_shared<GameObject>("DiskManager") };
	//AddGameObject(pDiskManager);
	//std::vector<DiskManager_Comp::DiskPos> diskPositions{
	//	{ DiskManager_Comp::DiskPos{ Transform::Side::Left,1 } },
	//	{ DiskManager_Comp::DiskPos{ Transform::Side::Right,1 } }
	//};
	//pDiskManager->AddComponent(new DiskManager_Comp(diskPositions));
}

void LevelScene::InitUi()
{
}

void LevelScene::InitWorld()
{
	const auto pNormalTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Normal.png") }
	, pIntermediateTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Intermediate.png") }
	, pHighlightTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Highlighted.png") };

	const auto bottomRowAmount{ 7 };
	auto pWorldGridManager{ std::make_shared<GameObject>("WorldTileManager") };
	AddGameObject(pWorldGridManager);
	pWorldGridManager->GetTransform()->ScaleUniform(.5f);
	pWorldGridManager->AddComponent(new WorldTileManager_Comp(pNormalTexture, pHighlightTexture, pIntermediateTexture, bottomRowAmount));
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