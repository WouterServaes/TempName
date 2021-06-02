#pragma once
#include <Observer.h>
class CreatureObserver final :public Observer
{
public:
	CreatureObserver() = default;
	~CreatureObserver() = default;
	CreatureObserver(const CreatureObserver& other) = delete;
	CreatureObserver(CreatureObserver&& other) noexcept = delete;
	CreatureObserver& operator=(const CreatureObserver& other) = delete;
	CreatureObserver& operator=(CreatureObserver&& other) noexcept = delete;

	void OnNotify(GameObject* pGameObject, Event event) override;
private:
	void FellOffGrid(GameObject* pGameObject);
};

