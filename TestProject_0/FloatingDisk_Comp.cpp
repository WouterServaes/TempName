#include "MiniginPCH.h"
#include "FloatingDisk_Comp.h"

#include "Animation_Comp.h"
#include "Scene.h"
#include "WorldTileManager_Comp.h"
FloatingDisk_Comp::FloatingDisk_Comp(const int pyramidRow, const Transform::Side pyramidSide) : m_PyramidRow(pyramidRow), m_PyramidSide(pyramidSide)
{
}

void FloatingDisk_Comp::Start()
{
	SetPositionOfDisk();
}

void FloatingDisk_Comp::SetPositionOfDisk()
{
	const auto tileManagerObj{ m_pGameObject->GetCurrentScene()->GetGameObject("WorldTileManager") };
	const auto* tileManagerComp{ tileManagerObj->GetConstComponent<WorldTileManager_Comp>() };
	
	const int botRowAmount{ tileManagerComp->GetBottomRowAmount() };
	if (m_PyramidRow > botRowAmount) Logger::LogWarning("FloatingDisk_Comp:: given row exceeds pyramids size, game object: " + m_pGameObject->GetName());
	
	const glm::vec2 tile0Pos{ tileManagerComp->GetTileStandPos(0) };
	const glm::vec2 tileDimensions{ tileManagerComp->GetGridTileDimensions() };

	auto* pTransform{ m_pGameObject->GetTransform() };
	const glm::vec2 textureDimensions{ GetComponent<Animation_Comp>()->GetFrameDimensions() * pTransform->GetScale() };

	glm::vec2 diskPos{};

	diskPos.y = tile0Pos.y - m_PyramidRow * tileDimensions.y + textureDimensions.y / 2.f;

	if(m_PyramidSide == Transform::Side::Left)
		diskPos.x = tile0Pos.x + (m_PyramidRow - 1) * (tileDimensions.x / 2.f);
	else	
		diskPos.x = tile0Pos.x + (botRowAmount - (botRowAmount - m_PyramidRow)) * tileDimensions.x;
	
	m_pGameObject->GetTransform()->SetPosition(diskPos.x, diskPos.y);
}
