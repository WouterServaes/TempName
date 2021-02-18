#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "TextComponent.h"

void dae::FpsComponent::Update()
{
	
	if (m_UseTextCompToPrint)
	{
		if (!m_IsInitialized)
		{
			m_IsInitialized = true;
			m_pTextComponent = m_pGameObject->GetComponent<TextComponent>();
		}

		const auto currentFps{ Time::GetInstance().fps };
		if(currentFps!=m_PreviousFps)
			m_pTextComponent->UpdateText(std::string("FPS:" + std::to_string(currentFps)));
		m_PreviousFps = currentFps;
	}
	
}