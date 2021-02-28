#pragma once
#include "BaseComponent.h"

namespace dae
{
	class HealthComponent final : public BaseComponent
	{
	public:
		explicit HealthComponent(float maxHealth = 10.f, float currentHealth = 5.f);
		~HealthComponent()  = default;
		[[nodiscard]]const float& GetHealth() const { return m_CurrentHealth; };
		bool RemoveHealth(float amount);
		void AddHealth(float amount);
	private:
		float m_CurrentHealth{};
		float m_MaxHealth{};
	};
	
}

