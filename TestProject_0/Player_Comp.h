#pragma once
#include <BaseComponent.h>

class CharacterController_Comp;
class Player_Comp final:public BaseComponent
{
public:
	Player_Comp() = default;
	~Player_Comp() = default;
	Player_Comp(const Player_Comp& other) = delete;
	Player_Comp(Player_Comp&& other) noexcept = delete;
	Player_Comp& operator=(const Player_Comp& other) = delete;
	Player_Comp& operator=(Player_Comp&& other) noexcept = delete;
	
	void Update() override;
	void Start() override;
private:
	void InitInput();
	CharacterController_Comp* m_pController{nullptr};
	bool m_Spawned{ false };
};

