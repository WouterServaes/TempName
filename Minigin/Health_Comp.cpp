#include "MiniginPCH.h"
#include "Health_Comp.h"


#include "Events.h"
#include "Subject.h"
#include "Text_Comp.h"

Health_Comp::Health_Comp(const int maxLives, const int currentLives)
	: m_CurrentLives(currentLives), m_MaxLives(maxLives)
{
}


void Health_Comp::Update()
{
	if(!m_UpdatedStartUi)
	{
		m_UpdatedStartUi = true;
		UpdateUi();
		
	}
}

void Health_Comp::AttachTextComp(Text_Comp* pTextComp)
{
	m_pHealthText = pTextComp;
}

void Health_Comp::UpdateUi() const
{
	if (!m_pHealthText)
	{
		Logger::LogInfo("Health_Comp on " + m_pGameObject->GetName() + " no text comp assigned!");
		return;
	}
	const auto text{ "Lives: " + std::to_string(m_CurrentLives) };
	m_pHealthText->UpdateText(text);
}

bool Health_Comp::RemoveLives(const int amount)
{
	m_CurrentLives -= amount;
	
	auto* pSubject{ m_pGameObject->GetSubject() };
	if (pSubject) pSubject->Notify(m_pGameObject, Event::LostLive);
	UpdateUi();
	return m_CurrentLives > 0;
}