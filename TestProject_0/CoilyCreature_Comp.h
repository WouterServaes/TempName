#pragma once
#include "Creature_Comp.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "Transform.h"

class Animation_Comp;
class DiskManager_Comp;
class CoilyCreature_Comp final:public Creature_Comp
{
public:
	CoilyCreature_Comp(float timeBetweenJumps
		, const std::string& coilyAnimationSheet, int coilyImageAmount, int coilyFramesPerSecond, glm::vec2 coilyFrameDimensions);
	~CoilyCreature_Comp() = default;
	CoilyCreature_Comp(const CoilyCreature_Comp & other) = delete;
	CoilyCreature_Comp(CoilyCreature_Comp && other) noexcept = delete;
	CoilyCreature_Comp& operator=(const CoilyCreature_Comp & other) = delete;
	CoilyCreature_Comp& operator=(CoilyCreature_Comp && other) noexcept = delete;
	void Spawn() override;
	void ResetCreature() override;
	void FellOffGrid();
	void PlayerJumpedOnDisk(glm::vec2 diskPosition);
private:
	void UpdateCreature() override;
	void CollidedWithPlayer() override;

	void UpdateEgg();
	void BounceToBottom();
	void ChangeToSnake();
	void ChangeToEgg();
	void FollowPlayer();

	float m_ElapsedTime{};
	const float m_TimeBetweenJumps;

	bool m_IsEgg{ true };

	Transform::Side m_LastSide{ Transform::Side::Left };

	const std::string m_CoilyAnimSheet;
	const int m_CoilyImageAmount, m_CoilyFPS;
	const glm::vec2 m_CoilyFrameDim;

	std::string m_EggAnimSheet{};
	int m_EggImageAmount{}, m_EggFPS{};
	glm::vec2 m_EggFrameDim{};
	
	Transform* m_pPlayerTransform{nullptr};
	Animation_Comp* m_pAnimationComp{ nullptr };
	DiskManager_Comp* m_pDiskManager{ nullptr };

	bool m_GoToDisk{ false };
	glm::vec2 m_DiskPos{};
	
	float m_OriginalScale{};

};

