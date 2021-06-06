#pragma once
#include <BaseComponent.h>

class GameController_Comp final:public BaseComponent
{
public:
	GameController_Comp() = default;
	~GameController_Comp() = default;
	GameController_Comp(const GameController_Comp& other) = delete;
	GameController_Comp(GameController_Comp&& other) noexcept = delete;
	GameController_Comp& operator=(const GameController_Comp& other) = delete;
	GameController_Comp& operator=(GameController_Comp&& other) noexcept = delete;
	void CompletedGrid();
	void PlayerDied();
	void ResetGame();
	void Start() override;
private:
	void CompletedGame();
	int m_CurrentLevel{ 1 };
	int m_PlayerDeadCount{};
	std::vector<std::shared_ptr<GameObject>> m_pPlayers;
};

