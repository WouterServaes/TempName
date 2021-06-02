#include "MiniginPCH.h"
#include "TileChanger_Comp.h"

#include "Events.h"
#include "Scene.h"
#include "Subject.h"
#include "Transform.h"
#include "WorldTileManager_Comp.h"
#include "WorldTile_Comp.h"

TileChanger_Comp::TileChanger_Comp(const TileChangeLevel tileChangeLevel)
	:m_TileChangeLevel(tileChangeLevel)
{
}

void TileChanger_Comp::Update()
{
	TryChangeTile();
}

void TileChanger_Comp::Start()
{
	m_pWorldTileManager = m_pGameObject->GetCurrentScene()->GetGameObject("WorldTileManager")->GetComponent<WorldTileManager_Comp>();
	m_pTransform = m_pGameObject->GetTransform();
}

void TileChanger_Comp::TryChangeTile()
{
	const auto pos{ m_pTransform->GetPosition() };

	if (pos != m_LastFramePos)
	{
		auto* pCurrentTile{ m_pWorldTileManager->GetTileAtPosition(pos) };
		ChangeTile(pCurrentTile);
	}
	m_LastFramePos = pos;
}

void TileChanger_Comp::ChangeTile(WorldTile_Comp* pTile) const
{
	if (!pTile) return;

	auto highlighted{ false };
	switch (m_TileChangeLevel)
	{
	case TileChangeLevel::ChangeOnce:
		if (!pTile->GetIsHighlighted())
		{
			pTile->ToHighlightedTexture();
			highlighted = true;
		}
		break;
	case TileChangeLevel::ChangeTwice:
		if (!pTile->GetIsHighlighted())
		{
			if (pTile->GetIsIntermediate())
				pTile->ToHighlightedTexture();
			else
				pTile->ToIntermediateTexture();
			highlighted = true;
		}

		break;
	case TileChangeLevel::ChangesBack:
		pTile->ToggleNormalHighlightedTexture();
		highlighted = pTile->GetIsHighlighted();
		break;
	case TileChangeLevel::RevertChanges:
		pTile->RevertTextureChange();
		highlighted = pTile->GetIsHighlighted();
		break;
	default:;
	}

	if (highlighted) FireEvent();
}

void TileChanger_Comp::FireEvent() const
{
	auto* pSubject = m_pGameObject->GetSubject();
	if (pSubject) pSubject->Notify(m_pGameObject, Event::ColorChanged);
}