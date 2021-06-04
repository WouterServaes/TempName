#include "MiniginPCH.h"
#include "FloatingDisk_Comp.h"

#include "Animation_Comp.h"
#include "Scene.h"
#include "WorldTileManager_Comp.h"

FloatingDisk_Comp::FloatingDisk_Comp(const DiskManager_Comp::DiskPos diskPos) : m_DiskPos(diskPos)
{
}

void FloatingDisk_Comp::Start()
{
	SetPositionOfDisk();
}

void FloatingDisk_Comp::SetPositionOfDisk()
{
	const auto pTileManagerObj{ m_pGameObject->GetCurrentScene()->GetGameObject("WorldTileManager") };
	const auto* pTileManagerComp{ pTileManagerObj->GetConstComponent<WorldTileManager_Comp>() };

	const int botRowAmount{ pTileManagerComp->GetBottomRowAmount() };
	if (m_DiskPos.pyramidRow > botRowAmount) Logger::LogWarning("FloatingDisk_Comp:: given row exceeds pyramids size, game object: " + m_pGameObject->GetName());

	const glm::vec2 tile0Pos{ pTileManagerComp->GetTileStandPos(0) };
	const glm::vec2 tileDimensions{ pTileManagerComp->GetGridTileDimensions() };

	auto* pTransform{ m_pGameObject->GetTransform() };
	const glm::vec2 textureDimensions{ GetComponent<Animation_Comp>()->GetFrameDimensions() * pTransform->GetScale() };

	glm::vec2 diskPos;
	glm::vec2 tilePos;

	tilePos.y = tile0Pos.y - m_DiskPos.pyramidRow * tileDimensions.y;
	diskPos.y = tilePos.y + textureDimensions.y / 2.f;

	if (m_DiskPos.pyramidSide == Transform::Side::Left)
	{
		tilePos.x = tile0Pos.x + (m_DiskPos.pyramidRow) * (tileDimensions.x / 2.f);
		diskPos.x = tile0Pos.x + (m_DiskPos.pyramidRow - 1) * (tileDimensions.x / 2.f);
	}
	else
	{
		tilePos.x = tile0Pos.x + (botRowAmount * tileDimensions.x) - (m_DiskPos.pyramidRow * tileDimensions.x / 2.f);
		diskPos.x = tile0Pos.x + (botRowAmount * tileDimensions.x) - (m_DiskPos.pyramidRow * tileDimensions.x / 2.f);
	}

	m_TileIdxNextToDisk = pTileManagerComp->GetTileIdxAtPosition(tilePos);
	m_pGameObject->GetTransform()->SetPosition(diskPos.x, diskPos.y);
}