#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "TextComponent.h"

void dae::FpsComponent::Update()
{
	if(m_UseTextCompToPrint)
		m_pGameObject->GetComponent<TextComponent>()->UpdateText(std::string("FPS:" + std::to_string(Time::GetInstance().fps)));
}