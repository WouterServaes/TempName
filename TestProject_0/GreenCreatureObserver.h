#pragma once
#include <Observer.h>
class GreenCreatureObserver final :public Observer
{
public:
	GreenCreatureObserver() = default;
	~GreenCreatureObserver() = default;
	GreenCreatureObserver(const GreenCreatureObserver& other) = delete;
	GreenCreatureObserver(GreenCreatureObserver&& other) noexcept = delete;
	GreenCreatureObserver& operator=(const GreenCreatureObserver& other) = delete;
	GreenCreatureObserver& operator=(GreenCreatureObserver&& other) noexcept = delete;

	void OnNotify(GameObject* pGameObject, Event event) override;
private:
	void FellOffGrid(GameObject* pGameObject);
};

