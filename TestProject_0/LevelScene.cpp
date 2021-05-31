#include "MiniginPCH.h"
#include "LevelScene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Transform.h"
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
	const auto pNormalTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Normal.png") }
	,pHighlightTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Highlighted.png") };

	const auto textDim{ pNormalTexture->GetTextureData().Dimensions };
	const auto tileWidth{ textDim.x },
		tileSmallestHeight{ textDim.y * 3.f/4.f};
	const auto bottomRowAmount{ 5 };
	auto pWorldGridManager{ std::make_shared<GameObject>(L"WorldGridManager", this) };
	AddGameObject(pWorldGridManager);
	pWorldGridManager->GetTransform()->SetPosition(50, 250);
	pWorldGridManager->AddComponent(new WorldTileManager_Comp(pNormalTexture, pHighlightTexture, tileWidth, tileSmallestHeight, bottomRowAmount));

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
