#include "MiniginPCH.h"
#include "TileChanger_Comp.h"

#include "Scene.h"
#include "Transform.h"
#include "WorldTileManager_Comp.h"
#include "WorldTile_Comp.h"

void TileChanger_Comp::Update()
{
	const auto pos{ m_pTransform->GetPosition() };
	
	if(pos != m_pTransform->GetLastPosition())
	{
		auto* pCurrentTile{ m_pWorldTileManager->GetTileAtPosition(pos) };
		if(pCurrentTile != nullptr)
			pCurrentTile->ToHighlightedTexture();
	}
}

void TileChanger_Comp::Start()
{
	m_pWorldTileManager = m_pGameObject->GetCurrentScene()->GetGameObject("WorldTileManager")->GetComponent<WorldTileManager_Comp>();
	m_pTransform = m_pGameObject->GetTransform();
}
