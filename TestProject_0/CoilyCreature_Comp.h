#pragma once
#include "Creature_Comp.h"
class CoilyCreature_Comp final:public Creature_Comp
{
public:
	CoilyCreature_Comp(float timeBetweenJumps);
	~CoilyCreature_Comp() = default;
	CoilyCreature_Comp(const CoilyCreature_Comp & other) = delete;
	CoilyCreature_Comp(CoilyCreature_Comp && other) noexcept = delete;
	CoilyCreature_Comp& operator=(const CoilyCreature_Comp & other) = delete;
	CoilyCreature_Comp& operator=(CoilyCreature_Comp && other) noexcept = delete;
	void Spawn() override;
private:
	void UpdateCreature() override;
	void CollidedWithPlayer() override;

	void UpdateEgg();
	void BounceToBottom();
	void ChangeToSnake();
	void FollowPlayer();
	
	float m_ElapsedTime{};
	const float m_TimeBetweenJumps;

	bool m_IsEgg{ true };

	Side m_LastSide{ Side::Left };
};

