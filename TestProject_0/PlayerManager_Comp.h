#pragma once
#include <BaseComponent.h>
class PlayerManager_Comp final:public BaseComponent
{
public:
	PlayerManager_Comp() = default;
	~PlayerManager_Comp() = default;
	PlayerManager_Comp(const PlayerManager_Comp & other) = delete;
	PlayerManager_Comp(PlayerManager_Comp && other) noexcept = delete;
	PlayerManager_Comp& operator=(const PlayerManager_Comp & other) = delete;
	PlayerManager_Comp& operator=(PlayerManager_Comp && other) noexcept = delete;
	void AddPlayer();

	const std::vector<std::shared_ptr<GameObject>>& GetPlayers() const;
	void ResetPlayers();
private:
	std::vector<std::shared_ptr<GameObject>> m_pPlayers{};
	int m_PlayerCount{};
	
};

