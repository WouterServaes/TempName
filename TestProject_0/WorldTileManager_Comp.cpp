#include "MiniginPCH.h"
#include "WorldTileManager_Comp.h"

#include "WorldTile_Comp.h"
#include "BaseComponent.h"
#include "Scene.h"

WorldTileManager_Comp::WorldTileManager_Comp(const std::shared_ptr<Texture2D> pNormalTexture,const std::shared_ptr<Texture2D> pHighlightTexture, const float spaceBetweenTiles, const int bottomRowAmount)
	: m_BottomRowAmount(bottomRowAmount), m_SpaceBetweenTiles(spaceBetweenTiles), m_pNormalTexture(pNormalTexture), m_pHighlightTexture(pHighlightTexture)
{
}

void WorldTileManager_Comp::Start()
{
	
}

void WorldTileManager_Comp::ResetTiles()
{
	for (auto& tile : m_pWorldTiles)
		tile->ToNormalTexture();
}

void WorldTileManager_Comp::SpawnTiles()
{
	//for every tile
		//make a game object
		//add render comp to this
		//calculate the correct location, set transform location to that
		//add WorldTile_Comp to this
			//use m_pNormalTexture and m_pHighlightTexture for textures
			//calculate correct standLocation
		//add WorldTile_Comp to vector
		//add game object to current scene
		//m_pGameObject->GetCurrentScene()->AddGameObject();
}
