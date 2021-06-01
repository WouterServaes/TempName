#pragma once
#include <BaseComponent.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
class CharacterController_Comp final:public BaseComponent
{
public:
	explicit CharacterController_Comp(float moveSpeed);
	~CharacterController_Comp() = default;
	CharacterController_Comp(const CharacterController_Comp& other) = delete;
	CharacterController_Comp(CharacterController_Comp&& other) noexcept = delete;
	CharacterController_Comp& operator=(const CharacterController_Comp& other) = delete;
	CharacterController_Comp& operator=(CharacterController_Comp&& other) noexcept = delete;

	void Move(glm::vec2 position);

	void Update() override;
	void Start() override;
private:
	[[nodiscard]] bool GetReachedPos() const;
	void UpdatePos();
	const float m_MoveSpeed;
	float m_ElapsedTime{};
	float m_MoveDelta{};
	glm::vec2 m_OrigPos, m_TargetPos{};
	Transform* m_pTransform{nullptr};
	bool m_IsMoving{ false };
	float m_DistanceToTravelSqred{};
	
};