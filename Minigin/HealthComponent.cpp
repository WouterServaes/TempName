#include "MiniginPCH.h"
#include "HealthComponent.h"


dae::HealthComponent::HealthComponent(const float maxHealth, const float currentHealth,const int maxLives, const int currentLives)
	:BaseComponent(componentType::health), m_MaxHealth(maxHealth), m_CurrentHealth(currentHealth), m_MaxLives(maxLives), m_CurrentLives(currentLives)
{
	
}


void dae::HealthComponent::AddHealth(const float amount)
{
	m_CurrentHealth += amount;
	if (m_CurrentHealth > m_MaxHealth)
		m_CurrentHealth = m_MaxHealth;
}

bool dae::HealthComponent::RemoveHealth(const float amount)
{
	m_CurrentHealth -= amount;
	return m_CurrentHealth > 0.f;
}

bool dae::HealthComponent::RemoveLives(int amount)
{
	m_CurrentLives -= amount;
	return m_CurrentLives > 0;
}

void dae::HealthComponent::ResetHealth()
{
	m_CurrentHealth = m_MaxHealth;
}


