#include "MiniginPCH.h"
#include "WorldTileManager_Comp.h"

#include "WorldTile_Comp.h"
#include "BaseComponent.h"
#include "Render_Comp.h"
#include "Scene.h"
#include "Transform.h"

WorldTileManager_Comp::WorldTileManager_Comp(const std::shared_ptr<Texture2D> pNormalTexture, const std::shared_ptr<Texture2D> pHighlightTexture, const float tileWidth, const float tileSmallestHeight, const int bottomRowAmount)
	: m_BottomRowAmount(bottomRowAmount), m_TileWidth(tileWidth), m_TileSmallestHeight(tileSmallestHeight), m_pNormalTexture(pNormalTexture), m_pHighlightTexture(pHighlightTexture)
{
}

void WorldTileManager_Comp::Start()
{
	
	SpawnTiles();
}

void WorldTileManager_Comp::ResetTiles()
{
	for (auto& tile : m_pWorldTiles)
		tile->ToNormalTexture();
}

void WorldTileManager_Comp::SpawnTiles()
{
	const auto& startPos{ m_pGameObject->GetTransform()->GetPosition() };
	glm::vec3 pos{ startPos };
	//pos.y -= m_BottomRowAmount * (m_TileSmallestHeight * 4.f);
	for (int row{}; row < m_BottomRowAmount; row++)
	{		
		for (int column{}; column < m_BottomRowAmount - row; column++)
		{
			//next tile
			const auto name{ std::wstring(L"Hex " + std::to_wstring(row) + L" " + std::to_wstring(column)) };
			auto pHexObj{ std::make_shared< GameObject>(name.c_str(), m_pGameObject->GetCurrentScene()) };
			pHexObj->GetTransform()->SetPosition(pos);
			pHexObj->AddComponent(new Render_Comp());
			auto* pTile{ new WorldTile_Comp(m_pNormalTexture, m_pHighlightTexture, glm::vec2(pos.x, pos.y)) };
			pHexObj->AddComponent(pTile);
			pTile->ToNormalTexture();
			m_pGameObject->GetCurrentScene()->AddGameObject(pHexObj);
			pos.x += m_TileWidth;
		}
		
		//next row
		pos.y -= m_TileSmallestHeight;

		//shift row
		pos.x = startPos.x + (m_TileWidth / 2.f) * (row+1);
	}

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