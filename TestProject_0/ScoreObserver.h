#pragma once
#include <Observer.h>
class ScoreObserver final:public Observer
{
public:
	ScoreObserver() = default;
	~ScoreObserver() = default;
	ScoreObserver(const ScoreObserver& other) = delete;
	ScoreObserver(ScoreObserver&& other) noexcept = delete;
	ScoreObserver& operator=(const ScoreObserver& other) = delete;
	ScoreObserver& operator=(ScoreObserver&& other) noexcept = delete;
	void OnNotify(GameObject* pGameObject, Event event) override;
private:
	void IncreaseScore(GameObject* pGameObject, int amount);
};

