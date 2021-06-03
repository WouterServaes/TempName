#pragma once
#include "Creature_Comp.h"

class GreenCreature_Comp final :public Creature_Comp
{
public:
	explicit GreenCreature_Comp(float timeBetweenJumps);
	~GreenCreature_Comp() = default;
	GreenCreature_Comp(const GreenCreature_Comp& other) = delete;
	GreenCreature_Comp(GreenCreature_Comp&& other) noexcept = delete;
	GreenCreature_Comp& operator=(const GreenCreature_Comp& other) = delete;
	GreenCreature_Comp& operator=(GreenCreature_Comp&& other) noexcept = delete;
	void UpdateCreature() override;
	void Respawn() override;
private:
	void Spawn() override;

	void CollidedWithPlayer() override;
	void HandleDead();
	void HandleAlive();
	Side m_FollowingSide{};
	float m_ElapsedTime{};
	const float m_TimeBetweenJumps;

	const float m_DeadCooldown{5.f};
	bool m_Dead{ false };
	float m_origScale{};
};

