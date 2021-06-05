#pragma once
#include "BaseComponent.h"

class Text_Comp;
class Health_Comp final : public BaseComponent
{
public:
	explicit Health_Comp(int maxLives = 1, int currentLives = 1);
	~Health_Comp() = default;
	Health_Comp(const Health_Comp& other) = delete;
	Health_Comp(Health_Comp&& other) noexcept = delete;
	Health_Comp& operator=(const Health_Comp& other) = delete;
	Health_Comp& operator=(Health_Comp&& other) noexcept = delete;

	void Update() override;
	void AttachTextComp(Text_Comp* pTextComp);
	[[nodiscard]] const int& GetLives() const { return m_CurrentLives; };
	bool RemoveLives(int amount = 1);

	[[nodiscard]] bool IsDead() const { return m_CurrentLives <= 0; }

	void ResetHealth();
private:
	void UpdateUi() const;
	int m_CurrentLives;
	const int m_MaxLives;

	Text_Comp* m_pHealthText{ nullptr };
	bool m_UpdatedStartUi{ false };
};
