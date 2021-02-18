#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "TextComponent.h"

void dae::FpsComponent::Update()
{
	if (!m_IsInitialized)
	{
		m_IsInitialized = true;
		m_pTextComponent = m_pGameObject->GetComponent<TextComponent>();
	}
	
	if (m_UseTextCompToPrint)
		m_pTextComponent->UpdateText(std::string("FPS:" + std::to_string(Time::GetInstance().fps)));
	
}