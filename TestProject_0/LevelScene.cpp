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
