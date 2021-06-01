#include "MiniginPCH.h"
#include "WorldTile_Comp.h"
#include "BaseComponent.h"
#include "Render_Comp.h"
WorldTile_Comp::WorldTile_Comp(const std::shared_ptr<Texture2D> pNormalTexture, const std::shared_ptr<Texture2D> pHighlightTexture, const glm::vec2 standLocation)
	:m_StandPosition(standLocation), m_pNormalTexture(pNormalTexture), m_pHighlightTexture(pHighlightTexture)
{}

void WorldTile_Comp::ChangeTexture()
{
	m_IsHighlighted = !m_IsHighlighted;
	auto pRend{ GetComponent<Render_Comp>() };
	pRend->UpdateTexture((m_IsHighlighted) ? m_pHighlightTexture : m_pNormalTexture);
}

void WorldTile_Comp::ToNormalTexture()
{
	if(m_IsHighlighted)
	{
		m_IsHighlighted = false;
		auto pRend{ GetComponent<Render_Comp>() };
		pRend->UpdateTexture(m_pNormalTexture);
	}
}

void WorldTile_Comp::ToHighlightedTexture()
{
	if(!m_IsHighlighted)
	{
		m_IsHighlighted = true;
		auto pRend{ GetComponent<Render_Comp>() };
		pRend->UpdateTexture(m_pHighlightTexture);
	}
}

	
	
