#pragma once
#include <BaseComponent.h>
class WorldTileManager_Comp;
class Transform;
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

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
	void SetLevel(int level);
private:
	void TryChangeTile();
	void FireEvent() const;
	WorldTileManager_Comp* m_pWorldTileManager{};
	Transform* m_pTransform{};
	glm::vec3 m_LastFramePos{};
	int m_Level{ 1 };
};

