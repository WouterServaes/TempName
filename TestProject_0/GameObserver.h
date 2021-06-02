#pragma once
#include <Observer.h>
class GameObserver final:public Observer
{
public:
	GameObserver() = default;
	~GameObserver() = default;
	GameObserver(const GameObserver & other) = delete;
	GameObserver(GameObserver && other) noexcept = delete;
	GameObserver& operator=(const GameObserver & other) = delete;
	GameObserver& operator=(GameObserver && other) noexcept = delete;
	void OnNotify(GameObject * pGameObject, Event event) override;
private:
	void GridComplete(GameObject* pGameObject);
};

