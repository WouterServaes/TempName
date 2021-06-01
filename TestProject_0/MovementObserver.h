#pragma once
#include <Observer.h>
class MovementObserver final:public Observer
{
public:
	MovementObserver() = default;
	~MovementObserver() = default;
	MovementObserver(const MovementObserver& other) = delete;
	MovementObserver(MovementObserver&& other) noexcept = delete;
	MovementObserver& operator=(const MovementObserver& other) = delete;
	MovementObserver& operator=(MovementObserver&& other) noexcept = delete;
	
	void OnNotify(GameObject* pGameObject, Event event) override;
private:
	void MoveLeftUp(GameObject* pGameObject) const;
	void MoveLeftDown(GameObject* pGameObject)const;
	void MoveRightUp(GameObject* pGameObject)const;
	void MoveRightDown(GameObject* pGameObject)const;
	void MoveRight(GameObject* pGameObject)const;
	void MoveLeft(GameObject* pGameObject)const;
};

