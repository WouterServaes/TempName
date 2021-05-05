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
	GetComponent<Render_Comp>()->UpdateTexture((m_IsHighlighted) ? m_pHighlightTexture : m_pNormalTexture);
}

void WorldTile_Comp::ToNormalTexture()
{
	if(m_IsHighlighted)
	{
		m_IsHighlighted = false;
		GetComponent<Render_Comp>()->UpdateTexture(m_pNormalTexture);
	}
}
	
	
