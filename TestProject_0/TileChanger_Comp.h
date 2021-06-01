#pragma once
#include <BaseComponent.h>
class WorldTileManager_Comp;
class Transform;
class TileChanger_Comp final:public BaseComponent
{
public:
	TileChanger_Comp() = default;
	~TileChanger_Comp() = default;
	TileChanger_Comp(const TileChanger_Comp& other) = delete;
	TileChanger_Comp(TileChanger_Comp&& other) noexcept = delete;
	TileChanger_Comp& operator=(const TileChanger_Comp& other) = delete;
	TileChanger_Comp& operator=(TileChanger_Comp&& other) noexcept = delete;
	void Update() override;
	void Start() override;
private:
	WorldTileManager_Comp* m_pWorldTileManager{};
	Transform* m_pTransform{};
};

