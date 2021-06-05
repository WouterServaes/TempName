#pragma once
#include "Creature_Comp.h"
#include "Transform.h"
class PurpleCreature_Comp final:public Creature_Comp
{
public:
	PurpleCreature_Comp(Transform::Side spawnSide, float timeBetweenJumps);
	~PurpleCreature_Comp() = default;
	PurpleCreature_Comp(const PurpleCreature_Comp& other) = delete;
	PurpleCreature_Comp(PurpleCreature_Comp&& other) noexcept = delete;
	PurpleCreature_Comp& operator=(const PurpleCreature_Comp& other) = delete;
	PurpleCreature_Comp& operator=(PurpleCreature_Comp&& other) noexcept = delete;
	void UpdateCreature() override;
	void ResetCreature() override;
private:
	void Spawn() override;
	void CollidedWithPlayer() override;
	Transform::Side m_SpawnSide;
	float m_ElapsedTime{};
	const float m_TimeBetweenJumps;
};

