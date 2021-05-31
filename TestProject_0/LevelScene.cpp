#include "MiniginPCH.h"
#include "LevelScene.h"


#include "CharacterController_Comp.h"
#include "EngineSettings.h"
#include "GameObject.h"
#include "Render_Comp.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Transform.h"
#include "WorldTileManager_Comp.h"
void LevelScene::InitializeScene()
{
	
	//InitWorld();
	const auto pTestCharText{ ResourceManager::GetInstance().LoadTexture("Images/logo.png") };
	auto* pCharContrComp{ new CharacterController_Comp(.5f) };
	auto pTestChar{ std::make_shared<GameObject>(L"aaa", this) };
	AddGameObject(pTestChar);
	pTestChar->AddComponent(pCharContrComp);
	pTestChar->AddComponent(new Render_Comp(pTestCharText));
}

void LevelScene::InitUi()
{
}

void LevelScene::InitWorld()
{
	const auto pNormalTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Normal.png") }
	,pHighlightTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Highlighted.png") };

	const auto scale{ .5f };
	
	const auto bottomRowAmount{ 5 };
	auto pWorldGridManager{ std::make_shared<GameObject>(L"WorldGridManager", this) };
	AddGameObject(pWorldGridManager);
	pWorldGridManager->AddComponent(new WorldTileManager_Comp(pNormalTexture, pHighlightTexture, scale, bottomRowAmount));

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
