#include "MiniginPCH.h"
#include "WorldTileManager_Comp.h"

#include "WorldTile_Comp.h"
#include "BaseComponent.h"
#include "EngineSettings.h"
#include "Minigin.h"
#include "Render_Comp.h"
#include "Scene.h"
#include "Transform.h"

WorldTileManager_Comp::WorldTileManager_Comp(const std::shared_ptr<Texture2D> pNormalTexture, const std::shared_ptr<Texture2D> pHighlightTexture, const float scale, const int bottomRowAmount)
	: m_BottomRowAmount(bottomRowAmount), m_Scale(scale), m_pNormalTexture(pNormalTexture), m_pHighlightTexture(pHighlightTexture)
{
	const auto textDim{ pNormalTexture->GetTextureData().Dimensions };
	m_TileWidth = textDim.x * m_Scale;
	m_TileSmallestHeight =  textDim.y * m_Scale * 3.f / 4.f  ;
}

WorldTileManager_Comp::~WorldTileManager_Comp()
{
	m_pWorldTiles.clear();
}

void WorldTileManager_Comp::Start()
{
	auto* pEngineSettings{ Minigin::pEngineSettings };
	const auto bottomMargin{ 20.f };
	const auto x{ static_cast<float>(pEngineSettings->WindowWidth) / 2.f - static_cast<float>(m_BottomRowAmount) / 2.f * m_TileWidth },
	y{ static_cast<float>(pEngineSettings->WindowHeight) - m_TileWidth - bottomMargin };
	m_pGameObject->GetTransform()->SetPosition(x, y);
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
	for (int row{}; row < m_BottomRowAmount; row++)
	{		
		for (int column{}; column < m_BottomRowAmount - row; column++)
		{
			//next tile
			const auto name{ std::wstring(L"Hex " + std::to_wstring(row) + L" " + std::to_wstring(column)) };
			auto pHexObj{ std::make_shared< GameObject>(name.c_str(), m_pGameObject->GetCurrentScene()) };
			pHexObj->GetTransform()->SetPosition(pos);
			pHexObj->AddComponent(new Render_Comp());
			auto* pTileComp{ new WorldTile_Comp(m_pNormalTexture, m_pHighlightTexture, glm::vec2(pos.x, pos.y), m_Scale) };
			m_pWorldTiles.push_back(pTileComp);
			auto* pTile{ pTileComp };
			
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