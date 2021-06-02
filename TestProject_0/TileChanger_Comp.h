#pragma once
#include <BaseComponent.h>
class WorldTileManager_Comp;
class Transform;
class WorldTile_Comp;
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

class TileChanger_Comp final :public BaseComponent
{
public:
	enum class TileChangeLevel
	{
		ChangeOnce, //jumping once changes color, jumping again doesn't change anything
		ChangeTwice, //jumping once changes to intermediate color, another time and it's complete. 
		ChangesBack, //toggles every jump
		RevertChanges //toggles already changed tiles
	};
	
	TileChanger_Comp() = default;
	TileChanger_Comp(TileChangeLevel tileChangeLevel);
	~TileChanger_Comp() = default;
	TileChanger_Comp(const TileChanger_Comp& other) = delete;
	TileChanger_Comp(TileChanger_Comp&& other) noexcept = delete;
	TileChanger_Comp& operator=(const TileChanger_Comp& other) = delete;
	TileChanger_Comp& operator=(TileChanger_Comp&& other) noexcept = delete;
	void Update() override;
	void Start() override;

	

private:
	void TryChangeTile();
	void ChangeTile(WorldTile_Comp* pTile) const;
	void FireEvent() const;
	WorldTileManager_Comp* m_pWorldTileManager{};
	Transform* m_pTransform{};
	glm::vec3 m_LastFramePos{};
	TileChangeLevel m_TileChangeLevel{ TileChangeLevel::ChangeOnce };
};
