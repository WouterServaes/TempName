#pragma once
#include "Creature_Comp.h"
class PurpleCreature_Comp final:public Creature_Comp
{
public:
	PurpleCreature_Comp(Side spawnSide, float timeBetweenJumps);
	~PurpleCreature_Comp() = default;
	PurpleCreature_Comp(const PurpleCreature_Comp& other) = delete;
	PurpleCreature_Comp(PurpleCreature_Comp&& other) noexcept = delete;
	PurpleCreature_Comp& operator=(const PurpleCreature_Comp& other) = delete;
	PurpleCreature_Comp& operator=(PurpleCreature_Comp&& other) noexcept = delete;
	void Update() override;
private:
	void Spawn() override;
	Side m_SpawnSide;
	float m_ElapsedTime{};
	const float m_TimeBetweenJumps;
};

