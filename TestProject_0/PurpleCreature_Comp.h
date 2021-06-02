#pragma once
#include <BaseComponent.h>
class CharacterController_Comp;
class WorldTileManager_Comp;
class Transform;
class PurpleCreature_Comp final :public BaseComponent
{
public:
	PurpleCreature_Comp(float timeBetweenJumps);
	~PurpleCreature_Comp() = default;
	PurpleCreature_Comp(const PurpleCreature_Comp& other) = delete;
	PurpleCreature_Comp(PurpleCreature_Comp&& other) noexcept = delete;
	PurpleCreature_Comp& operator=(const PurpleCreature_Comp& other) = delete;
	PurpleCreature_Comp& operator=(PurpleCreature_Comp&& other) noexcept = delete;
	void Start() override;
	void Update() override;
private:
	enum class Side
	{
		Left, Right
	};
	void Spawn();
	CharacterController_Comp* m_pCharacterController{ nullptr };
	WorldTileManager_Comp* m_pWorldTileManager{ nullptr };
	Transform* m_pTransform{ nullptr };
	Side m_FollowingSide{};
	float m_ElapsedTime{};
	const float m_TimeBetweenJumps;
};

