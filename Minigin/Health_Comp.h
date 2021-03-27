#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Health_Comp final : public BaseComponent
	{
	public:
		explicit Health_Comp(float maxHealth = 10.f, float currentHealth = 5.f, int maxLives = 1, int currentLives = 1);
		~Health_Comp()  = default;
		[[nodiscard]]const float& GetHealth() const { return m_CurrentHealth; };
		bool RemoveHealth(float amount);
		void AddHealth(float amount);
		void ResetHealth();
		[[nodiscard]] const int& GetLives() const { return m_CurrentLives; };
		bool RemoveLives(int amount = 1);
	private:
		float m_CurrentHealth;
		const float m_MaxHealth;

		int m_CurrentLives;
		const int m_MaxLives;
	};
	
}

