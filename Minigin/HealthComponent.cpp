#include "MiniginPCH.h"
#include "HealthComponent.h"


dae::HealthComponent::HealthComponent(const float maxHealth, const float currentHealth)
	:BaseComponent(componentType::health), m_MaxHealth(maxHealth), m_CurrentHealth(currentHealth)
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
	return m_CurrentHealth <= 0.f;
}
