#pragma once
#include <BaseComponent.h>
#include "Transform.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
class WorldTileManager_Comp;
class FloatingDisk_Comp;
class DiskManager_Comp final :public BaseComponent
{
public:
	struct DiskPos
	{
		Transform::Side pyramidSide;
		int pyramidRow;
	};

	explicit DiskManager_Comp(std::vector<DiskPos>& diskPositions);
	~DiskManager_Comp() = default;
	DiskManager_Comp(const DiskManager_Comp& other) = delete;
	DiskManager_Comp(DiskManager_Comp&& other) noexcept = delete;
	DiskManager_Comp& operator=(const DiskManager_Comp& other) = delete;
	DiskManager_Comp& operator=(DiskManager_Comp&& other) noexcept = delete;

	void Start() override;

	[[nodiscard]] bool IsDiskNextToPos(glm::vec2 position) const;

private:
	void MakeDisks();
	const std::vector<DiskPos> m_DiskPositions;
	std::vector<FloatingDisk_Comp*> m_pDisks;
	WorldTileManager_Comp* m_pWorldTileManager{ nullptr };
};
