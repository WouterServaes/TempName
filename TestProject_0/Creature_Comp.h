#pragma once
#include <BaseComponent.h>
class CharacterController_Comp;
class WorldTileManager_Comp;
class Transform;

class Creature_Comp :public BaseComponent
{
public:
	Creature_Comp() = default;
	virtual ~Creature_Comp() = default;
	Creature_Comp(const Creature_Comp & other) = delete;
	Creature_Comp(Creature_Comp && other) noexcept = delete;
	Creature_Comp& operator=(const Creature_Comp & other) = delete;
	Creature_Comp& operator=(Creature_Comp && other) noexcept = delete;
	virtual void Respawn() = 0;
	void Update() override = 0;
	void Start() override;
private:
	virtual void Spawn() = 0;

	
protected:
	CharacterController_Comp* m_pCharacterController{ nullptr };
	WorldTileManager_Comp* m_pWorldTileManager{ nullptr };
	Transform* m_pTransform{ nullptr };
};

