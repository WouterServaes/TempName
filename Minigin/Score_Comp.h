#pragma once
#include "BaseComponent.h"

class Text_Comp;
class Score_Comp final :public BaseComponent
{
public:
	Score_Comp() = default;
	~Score_Comp() = default;
	Score_Comp(const Score_Comp& other) = delete;
	Score_Comp(Score_Comp&& other) noexcept = delete;
	Score_Comp& operator=(const Score_Comp& other) = delete;
	Score_Comp& operator=(Score_Comp&& other) noexcept = delete;
	void Update() override;
	void AttachTextComp(Text_Comp* pTextComp);
	[[nodiscard]] const int& GetScore()const { return m_CurrentScore; };
	void SetScore(int newScore);
	void IncreaseScore(int amount);
	void ResetScore();
private:
	void UpdateUi() const;
	int m_CurrentScore{};
	Text_Comp* m_pScoreText{nullptr};
	bool m_UpdatedStartUi{ false };
};
