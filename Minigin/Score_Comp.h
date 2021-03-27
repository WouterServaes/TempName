#pragma once
#include "BaseComponent.h"
namespace dae
{
	class Score_Comp :
	    public BaseComponent
	{
	public:
		Score_Comp()=default;
		~Score_Comp() = default;

		[[nodiscard]]const int& GetScore()const { return m_CurrentScore; };
		void SetScore(const int newScore) { m_CurrentScore = newScore; };
		void IncreaseScore(const int amount) { m_CurrentScore += amount; };
		void ResetScore() { m_CurrentScore = 0; };
	private:
		int m_CurrentScore{};
		
	};
	
}

