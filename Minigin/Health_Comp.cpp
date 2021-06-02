#include "MiniginPCH.h"
#include "Health_Comp.h"


#include "Events.h"
#include "Subject.h"

Health_Comp::Health_Comp(const float maxHealth, const float currentHealth, const int maxLives, const int currentLives)
	:m_MaxHealth(maxHealth), m_CurrentHealth(currentHealth), m_MaxLives(maxLives), m_CurrentLives(currentLives)
{
}

void Health_Comp::AddHealth(const float amount)
{
	m_CurrentHealth += amount;
	if (m_CurrentHealth > m_MaxHealth)
		m_CurrentHealth = m_MaxHealth;
}

bool Health_Comp::RemoveHealth(const float amount)
{
	m_CurrentHealth -= amount;
	return m_CurrentHealth > 0.f;
}

bool Health_Comp::RemoveLives(const int amount)
{
	m_CurrentLives -= amount;
	
	auto* pSubject{ m_pGameObject->GetSubject() };
	if (pSubject) pSubject->Notify(m_pGameObject, Event::LostLive);
	
	return m_CurrentLives > 0;
}

void Health_Comp::ResetHealth()
{
	m_CurrentHealth = m_MaxHealth;
}