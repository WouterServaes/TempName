#pragma once
#include <BaseComponent.h>
class CharacterController_Comp;
class WorldTileManager_Comp;
class Transform;
class GreenCreature_Comp final :public BaseComponent
{
public:
	explicit GreenCreature_Comp(float timeBetweenJumps);
	~GreenCreature_Comp() = default;
	GreenCreature_Comp(const GreenCreature_Comp& other) = delete;
	GreenCreature_Comp(GreenCreature_Comp&& other) noexcept = delete;
	GreenCreature_Comp& operator=(const GreenCreature_Comp& other) = delete;
	GreenCreature_Comp& operator=(GreenCreature_Comp&& other) noexcept = delete;
	void Start() override;
	void Update() override;
	void Respawn();
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

