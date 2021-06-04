#include "MiniginPCH.h"
#include "WorldTileManager_Comp.h"

#include "WorldTile_Comp.h"
#include "BaseComponent.h"
#include "EngineSettings.h"
#include "Events.h"
#include "Minigin.h"
#include "Render_Comp.h"
#include "Scene.h"
#include "Subject.h"
#include "Transform.h"

WorldTileManager_Comp::WorldTileManager_Comp(const std::shared_ptr<Texture2D> pNormalTexture, const std::shared_ptr<Texture2D> pHighlightTexture, std::shared_ptr<Texture2D> pIntermediateTexture, const int bottomRowAmount)
	: m_BottomRowAmount(bottomRowAmount),
	m_pNormalTexture(pNormalTexture),
	m_pHighlightTexture(pHighlightTexture),
	m_pIntermediateTexture(pIntermediateTexture)
{
}

void WorldTileManager_Comp::Start()
{
	//texture/tile dimensions
	const auto textDim{ m_pNormalTexture->GetTextureData().Dimensions };
	auto* pTransform{ m_pGameObject->GetTransform() };
	const auto scale{ pTransform->GetUniformScale() };
	m_TileWidth = textDim.x * scale;
	m_TileSmallestHeight = textDim.y * scale * 3.f / 4.f;

	//tile stand offset
	m_TileStandOffset.x = m_TileWidth / 2.f;
	m_TileStandOffset.y = m_TileSmallestHeight / 2.f;

	//pyramid position
	auto* pEngineSettings{ Minigin::pEngineSettings };
	const auto bottomMargin{ 20.f };
	const auto x{ static_cast<float>(pEngineSettings->WindowWidth) / 2.f - static_cast<float>(m_BottomRowAmount) / 2.f * m_TileWidth },
		y{ static_cast<float>(pEngineSettings->WindowHeight) - m_TileWidth - bottomMargin };
	pTransform->SetPosition(x, y);

	SpawnTiles();
}

void WorldTileManager_Comp::Update()
{
	CheckIfCompleted();
}

glm::vec2 WorldTileManager_Comp::GetGridTileStandOffset() const
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

WorldTile_Comp* WorldTileManager_Comp::GetTileAtPosition(glm::vec2 position) const
{
	const auto it{ std::find_if(m_pWorldTiles.begin(), m_pWorldTiles.end(), [position, this](WorldTile_Comp* pWorldTile)
		{
			const auto standPos{ pWorldTile->GetStandPos() };

			return position.x <= standPos.x + m_TileWidth / 2.f && position.x >= standPos.x - m_TileWidth / 2.f
				&& position.y == standPos.y;
		}) };

	if (it != m_pWorldTiles.end())
		return *it;
	return nullptr;
}

int WorldTileManager_Comp::GetTileIdxAtPosition(glm::vec2 position) const
{
	const auto it{ std::find_if(m_pWorldTiles.begin(), m_pWorldTiles.end(), [position, this](WorldTile_Comp* pWorldTile)
		{
			const auto standPos{ pWorldTile->GetStandPos() };

			return position.x <= standPos.x + m_TileWidth / 2.f && position.x >= standPos.x - m_TileWidth / 2.f
				&& position.y == standPos.y;
		}) };

	int idx{ -1 };
	if (it != m_pWorldTiles.end())
		idx = static_cast<int>(std::distance(m_pWorldTiles.begin(), it));
	return idx;
}

bool WorldTileManager_Comp::IsTileAtPosition(const glm::vec2 position) const
{
	return GetTileAtPosition(position) != nullptr;
}

int WorldTileManager_Comp::GetTileAmount() const
{
	return static_cast<int>(m_pWorldTiles.size()) - 1;
}

int WorldTileManager_Comp::GetBottomRowAmount() const
{
	return m_BottomRowAmount - 1;
}

glm::vec2 WorldTileManager_Comp::GetGridTileDimensions() const
{
	return glm::vec2(m_TileWidth, m_TileSmallestHeight);
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

	auto* pHexTransform{ pHexObj->GetTransform() };
	pHexTransform->SetPosition(pos);
	pHexTransform->ScaleUniform(m_pGameObject->GetTransform()->GetUniformScale());

	pHexObj->AddComponent(new Render_Comp());

	auto* pTileComp{ new WorldTile_Comp(m_pNormalTexture, m_pHighlightTexture, m_pIntermediateTexture, glm::vec2(pos.x + m_TileStandOffset.x, pos.y - m_TileStandOffset.y)) };
	m_pWorldTiles.push_back(pTileComp);

	pHexObj->AddComponent(pTileComp);
	pTileComp->ToNormalTexture();

	m_pGameObject->GetCurrentScene()->AddGameObject(pHexObj);
	pHexObj->SetRenderLayer(-1);
}

void WorldTileManager_Comp::CheckIfCompleted() const
{
	const auto it{ std::find_if(m_pWorldTiles.begin(), m_pWorldTiles.end(), [](WorldTile_Comp* pTile) { return !pTile->GetIsHighlighted(); }) };
	if (it == m_pWorldTiles.end())
	{
		const auto pGameController{ m_pGameObject->GetCurrentScene()->GetGameObject("GameController") };
		pGameController->GetSubject()->Notify(pGameController.get(), Event::GridComplete);
	}
}