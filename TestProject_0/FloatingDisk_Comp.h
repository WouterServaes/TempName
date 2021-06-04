#pragma once
#include <BaseComponent.h>
#include "DiskManager_Comp.h"

class FloatingDisk_Comp final:public BaseComponent
{
public:
	FloatingDisk_Comp(DiskManager_Comp::DiskPos diskPos);
	~FloatingDisk_Comp() = default;
	FloatingDisk_Comp(const FloatingDisk_Comp & other) = delete;
	FloatingDisk_Comp(FloatingDisk_Comp && other) noexcept = delete;
	FloatingDisk_Comp& operator=(const FloatingDisk_Comp & other) = delete;
	FloatingDisk_Comp& operator=(FloatingDisk_Comp && other) noexcept = delete;

	void Start() override;

	[[nodiscard]] DiskManager_Comp::DiskPos GetDiskPos() const { return m_DiskPos; }
	[[nodiscard]] int GetTileIdxNextToDisk() const { return m_TileIdxNextToDisk; }
private:
	void SetPositionOfDisk();

	const DiskManager_Comp::DiskPos m_DiskPos;
	int m_TileIdxNextToDisk{};
};
