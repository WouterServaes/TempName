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
void LevelOneScene::InitializeScene()
{
	InitWorld();

	
	auto pPlayerObj{ std::make_shared< GameObject>("pl", true) };
	AddGameObject(pPlayerObj);
	pPlayerObj->AddComponent(new Render_Comp());
	auto* pAnimComp{ new Animation_Comp("Images/QBert.png", 4, 8, glm::vec2(128.f, 147.f)) };
	pPlayerObj->AddComponent(pAnimComp);
	pAnimComp->Scale(.25f);
	pPlayerObj->AddComponent(new CharacterController_Comp(.025f));
	pPlayerObj->AddComponent(new Player_Comp());
	pPlayerObj->GetSubject()->AddObserver(new MovementObserver());
	
	
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
	auto pWorldGridManager{ std::make_shared<GameObject>("WorldGridManager") };
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
