#include "MiniginPCH.h"
#include "LevelScene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "WorldTileManager_Comp.h"
void LevelScene::InitializeScene()
{
	InitUi();
	InitWorld();
}

void LevelScene::InitUi()
{
}

void LevelScene::InitWorld()
{
	const auto pNormalTexture{ ResourceManager::GetInstance().LoadTexture("") }
	,pHighlightTexture{ ResourceManager::GetInstance().LoadTexture("") };

	const auto spaceBetweenTiles{ 2.f };
	const auto bottomRowAmount{ 5 };
	auto pWorldGridManager{ std::make_shared<GameObject>(L"WorldGridManager", this) };
	pWorldGridManager->AddComponent(new WorldTileManager_Comp(pNormalTexture, pHighlightTexture, spaceBetweenTiles, bottomRowAmount));

	AddGameObject(pWorldGridManager);
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
