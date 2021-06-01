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
	: m_BottomRowAmount(bottomRowAmount), m_Scale(scale),
	m_pNormalTexture(pNormalTexture),
	m_pHighlightTexture(pHighlightTexture)
{
}

void WorldTileManager_Comp::Start()
{
	//texture/tile dimensions
	const auto textDim{ m_pNormalTexture->GetTextureData().Dimensions };
	m_TileWidth = textDim.x * m_Scale;
	m_TileSmallestHeight = textDim.y * m_Scale * 3.f / 4.f;

	//tile stand offset
	m_TileStandOffset.x = m_TileWidth / 2.f;
	m_TileStandOffset.y = m_TileSmallestHeight + m_TileSmallestHeight / 2.f;

	//pyramid position
	auto* pEngineSettings{ Minigin::pEngineSettings };
	const auto bottomMargin{ 20.f };
	const auto x{ static_cast<float>(pEngineSettings->WindowWidth) / 2.f - static_cast<float>(m_BottomRowAmount) / 2.f * m_TileWidth },
		y{ static_cast<float>(pEngineSettings->WindowHeight) - m_TileWidth - bottomMargin };
	m_pGameObject->GetTransform()->SetPosition(x, y);

	SpawnTiles();
}

glm::vec2 WorldTileManager_Comp::GetGridTileDimensions() const
{
	return m_TileStandOffset;
}

void WorldTileManager_Comp::ResetTiles()
{
	for (auto& tile : m_pWorldTiles)
		tile->ToNormalTexture();
}

glm::vec2 WorldTileManager_Comp::GetTileStandPos(const int tileIdx) const
{
	return m_pWorldTiles.at(tileIdx)->GetStandPos();
}

void WorldTileManager_Comp::SpawnTiles()
{
	const auto& startPos{ m_pGameObject->GetTransform()->GetPosition() };
	glm::vec3 pos{ startPos };
	for (int row{}; row < m_BottomRowAmount; row++)
	{
		for (int column{}; column < m_BottomRowAmount - row; column++)
		{
			CreateTile(pos, column, row);
			pos.x += m_TileWidth;
		}

		//next row
		pos.y -= m_TileSmallestHeight;

		//shift row
		pos.x = startPos.x + (m_TileWidth / 2.f) * (row + 1);
	}
}

void WorldTileManager_Comp::CreateTile(const glm::vec3 pos, const int c, const int r)
{
	auto name{ std::string("Hex " + std::to_string(r)) };
	name += " " + std::to_string(c);

	auto pHexObj{ std::make_shared< GameObject>(name.c_str()) };

	pHexObj->GetTransform()->SetPosition(pos);
	pHexObj->AddComponent(new Render_Comp());

	auto* pTileComp{ new WorldTile_Comp(m_pNormalTexture, m_pHighlightTexture, glm::vec2(pos.x + m_TileStandOffset.x, pos.y + m_TileStandOffset.y), m_Scale) };
	m_pWorldTiles.push_back(pTileComp);

	pHexObj->AddComponent(pTileComp);
	pTileComp->ToNormalTexture();

	m_pGameObject->GetCurrentScene()->AddGameObject(pHexObj);
}