#pragma once
#include "Observer.h"
//NOT USED 
class Text_Comp;
class Score_Comp;
class PlayerObserver final :
	public Observer
{
public:
	PlayerObserver() = default;
	~PlayerObserver() = default;
	PlayerObserver(const PlayerObserver& other) = delete;
	PlayerObserver(PlayerObserver&& other) noexcept = delete;
	PlayerObserver& operator=(const PlayerObserver& other) = delete;
	PlayerObserver& operator=(PlayerObserver&& other) noexcept = delete;

	void OnNotify(GameObject* gameObject, Event event) override;
private:
	//old:
	void UpdateHealthUi(const GameObject* gameObject);
	void ShowPlayerDied(GameObject* gameObject);
	void HandleDefeatedCoily(GameObject* gameObject);
	void HandleColorChanged(GameObject* gameObject);
	void HandleCatchedSlickOrSame(GameObject* gameObject);
	void HandleLeftDiskAtEnd(GameObject* gameObject);

	void HandleMove(GameObject* pGameObject);
	void AddScore(int amount, GameObject* playerObj);
	Text_Comp* GetScoreTextComponent(const GameObject* playerObj);
	Score_Comp* GetScoreComponent(GameObject* const playerObj);

	//new:
	
};
