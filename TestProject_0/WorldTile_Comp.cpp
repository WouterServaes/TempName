#include "MiniginPCH.h"
#include "WorldTile_Comp.h"
#include "BaseComponent.h"
#include "Render_Comp.h"
WorldTile_Comp::WorldTile_Comp(const std::shared_ptr<Texture2D> pNormalTexture, const std::shared_ptr<Texture2D> pHighlightTexture, std::shared_ptr<Texture2D> pIntermediateTexture, const glm::vec2 standLocation)
	:m_StandPosition(standLocation), m_pNormalTexture(pNormalTexture), m_pHighlightTexture(pHighlightTexture), m_pIntermediateTexture(pIntermediateTexture)
{}

void WorldTile_Comp::Start()
{
	m_pRenderComp = GetComponent<Render_Comp>();
	m_pRenderComp->UpdateTexture(m_pNormalTexture);
}

void WorldTile_Comp::ToggleNormalHighlightedTexture()
{
	if (m_TileLevel == TileLevel::Normal)
		ToHighlightedTexture();
	else
		ToNormalTexture();
}

void WorldTile_Comp::ToNormalTexture()
{
	if (m_TileLevel != TileLevel::Normal)
	{
		m_PrevTileLevel = m_TileLevel;
		m_TileLevel = TileLevel::Normal;

		m_pRenderComp->UpdateTexture(m_pNormalTexture);
	}
}

void WorldTile_Comp::ToHighlightedTexture()
{
	if (m_TileLevel != TileLevel::Highlighted)
	{
		m_PrevTileLevel = m_TileLevel;
		m_TileLevel = TileLevel::Highlighted;

		m_pRenderComp->UpdateTexture(m_pHighlightTexture);
	}
}

void WorldTile_Comp::ToIntermediateTexture()
{
	if (m_TileLevel != TileLevel::Intermediate)
	{
		m_PrevTileLevel = m_TileLevel;
		m_TileLevel = TileLevel::Intermediate;
		m_pRenderComp->UpdateTexture(m_pIntermediateTexture);
	}
}

void WorldTile_Comp::RevertTextureChange()
{
	if (m_PrevTileLevel == m_TileLevel) return;
	switch (m_PrevTileLevel)
	{
	case TileLevel::Normal:
		ToNormalTexture();
		break;
	case TileLevel::Intermediate:
		ToIntermediateTexture();
		break;
	case TileLevel::Highlighted:
		ToHighlightedTexture();
		break;
	}


}