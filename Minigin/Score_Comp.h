#pragma once
#include "BaseComponent.h"

class Score_Comp final :
	public BaseComponent
{
public:
	Score_Comp() = default;
	~Score_Comp() = default;
	Score_Comp(const Score_Comp& other) = delete;
	Score_Comp(Score_Comp&& other) noexcept = delete;
	Score_Comp& operator=(const Score_Comp& other) = delete;
	Score_Comp& operator=(Score_Comp&& other) noexcept = delete;

	[[nodiscard]] const int& GetScore()const { return m_CurrentScore; };
	void SetScore(const int newScore) { m_CurrentScore = newScore; };
	void IncreaseScore(const int amount) { m_CurrentScore += amount; };
	void ResetScore() { m_CurrentScore = 0; };
private:
	int m_CurrentScore{};
};
