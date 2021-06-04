#pragma once
#include "Creature_Comp.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "Transform.h"
class CoilyCreature_Comp final:public Creature_Comp
{
public:
	CoilyCreature_Comp(float timeBetweenJumps, const std::string& coilyAnimationSheet, int coilyImageAmount, int coilyFramesPerSecond, glm::vec2 coilyFrameDimensions);
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

	Transform::Side m_LastSide{ Transform::Side::Left };

	const std::string m_CoilyAnimSheet;
	const int m_CoilyImageAmount, m_CoilyFPS;
	const glm::vec2 m_CoilyFrameDim;

	Transform* m_pPlayerTransform{nullptr};
};

