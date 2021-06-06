#pragma once
#include <BaseComponent.h>

class CharacterController_Comp;
class Health_Comp;
class DiskManager_Comp;
class CoilyCreature_Comp;
class Player_Comp final:public BaseComponent
{
public:
	Player_Comp(int spawnTileIndex);
	~Player_Comp() = default;
	Player_Comp(const Player_Comp& other) = delete;
	Player_Comp(Player_Comp&& other) noexcept = delete;
	Player_Comp& operator=(const Player_Comp& other) = delete;
	Player_Comp& operator=(Player_Comp&& other) noexcept = delete;
	
	void Update() override;
	void Start() override;

	void NextLevel();
	void ResetPlayer();
	void FellOffPyramid();
private:
	void InitInput();
	void CheckIfDead() const;
	CharacterController_Comp* m_pController{nullptr};
	Health_Comp* m_pHealthComp{ nullptr };
	DiskManager_Comp* m_pDiskmanager{ nullptr };
	CoilyCreature_Comp* m_pCoily{ nullptr };
	const int m_SpawnTileIndex;
};

