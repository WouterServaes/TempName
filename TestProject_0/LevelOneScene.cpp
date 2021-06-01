#include "MiniginPCH.h"
#include "LevelOneScene.h"


#include "CharacterController_Comp.h"
#include "EngineSettings.h"
#include "GameObject.h"
#include "Render_Comp.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Transform.h"
#include "WorldTileManager_Comp.h"
void LevelOneScene::InitializeScene()
{
	InitWorld();
}

void LevelOneScene::InitUi()
{
}

void LevelOneScene::InitWorld()
{
	const auto pNormalTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Normal.png") }
	,pHighlightTexture{ ResourceManager::GetInstance().LoadTexture("Images/Tile_Highlighted.png") };

	const auto scale{ .5f };
	
	const auto bottomRowAmount{ 5 };
	auto pWorldGridManager{ std::make_shared<GameObject>(L"WorldGridManager", this) };
	AddGameObject(pWorldGridManager);
	pWorldGridManager->AddComponent(new WorldTileManager_Comp(pNormalTexture, pHighlightTexture, scale, bottomRowAmount));

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
