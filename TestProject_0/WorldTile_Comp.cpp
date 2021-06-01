#include "MiniginPCH.h"
#include "WorldTile_Comp.h"
#include "BaseComponent.h"
#include "Render_Comp.h"
WorldTile_Comp::WorldTile_Comp(const std::shared_ptr<Texture2D> pNormalTexture, const std::shared_ptr<Texture2D> pHighlightTexture, const glm::vec2 standLocation, const float scale)
	:m_StandPosition(standLocation), m_pNormalTexture(pNormalTexture), m_pHighlightTexture(pHighlightTexture), m_Scale(scale)
{}

void WorldTile_Comp::ChangeTexture()
{
	m_IsHighlighted = !m_IsHighlighted;
	auto pRend{ GetComponent<Render_Comp>() };
	pRend->UpdateTexture((m_IsHighlighted) ? m_pHighlightTexture : m_pNormalTexture);
	pRend->ScaleTexture(m_Scale, m_Scale);
}

void WorldTile_Comp::ToNormalTexture()
{
	if(m_IsHighlighted)
	{
		m_IsHighlighted = false;
		auto pRend{ GetComponent<Render_Comp>() };
		pRend->UpdateTexture(m_pNormalTexture);
		pRend->ScaleTexture(m_Scale, m_Scale);
	}
}

void WorldTile_Comp::Start()
{
	Logger::LogInfo((std::string("Added ") + std::string(m_pGameObject->GetName())).c_str());
}
	
	
