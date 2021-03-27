#include "MiniginPCH.h"
#include "Health_Comp.h"


dae::Health_Comp::Health_Comp(const float maxHealth, const float currentHealth,const int maxLives, const int currentLives)
	:BaseComponent(componentType::health), m_MaxHealth(maxHealth), m_CurrentHealth(currentHealth), m_MaxLives(maxLives), m_CurrentLives(currentLives)
{
	
}


void dae::Health_Comp::AddHealth(const float amount)
{
	m_CurrentHealth += amount;
	if (m_CurrentHealth > m_MaxHealth)
		m_CurrentHealth = m_MaxHealth;
}

bool dae::Health_Comp::RemoveHealth(const float amount)
{
	m_CurrentHealth -= amount;
	return m_CurrentHealth > 0.f;
}

bool dae::Health_Comp::RemoveLives(int amount)
{
	m_CurrentLives -= amount;
	return m_CurrentLives > 0;
}

void dae::Health_Comp::ResetHealth()
{
	m_CurrentHealth = m_MaxHealth;
}


