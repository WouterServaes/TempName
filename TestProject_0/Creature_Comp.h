#pragma once
#include <BaseComponent.h>
class CharacterController_Comp;
class WorldTileManager_Comp;
class Transform;
class Creature_Comp :public BaseComponent
{
public:
	Creature_Comp() = default;
	~Creature_Comp() = default;
	Creature_Comp(const Creature_Comp & other) = delete;
	Creature_Comp(Creature_Comp && other) noexcept = delete;
	Creature_Comp& operator=(const Creature_Comp & other) = delete;
	Creature_Comp& operator=(Creature_Comp && other) noexcept = delete;
	virtual void Respawn();
	void Update() override;
	void Start() override;
	enum class Side
	{
		Left, Right
	};
private:
	virtual void Spawn() = 0;
	virtual void UpdateCreature() = 0;
	virtual void CollidedWithPlayer() = 0;
protected:
	void CheckForPlayer();
	
	CharacterController_Comp* m_pCharacterController{ nullptr };
	WorldTileManager_Comp* m_pWorldTileManager{ nullptr };
	Transform* m_pTransform{ nullptr };
	std::shared_ptr<GameObject> m_pPlayer{ nullptr };

};

