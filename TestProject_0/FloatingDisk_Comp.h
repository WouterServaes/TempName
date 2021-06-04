#pragma once
#include <BaseComponent.h>
#include "Transform.h"
class FloatingDisk_Comp final:public BaseComponent
{
public:
	FloatingDisk_Comp(int pyramidRow, Transform::Side pyramidSide);
	~FloatingDisk_Comp() = default;
	FloatingDisk_Comp(const FloatingDisk_Comp & other) = delete;
	FloatingDisk_Comp(FloatingDisk_Comp && other) noexcept = delete;
	FloatingDisk_Comp& operator=(const FloatingDisk_Comp & other) = delete;
	FloatingDisk_Comp& operator=(FloatingDisk_Comp && other) noexcept = delete;

	void Start() override;

	[[nodiscard]] Transform::Side GetPyramidSideOfDisk()const { return m_PyramidSide; }
	[[nodiscard]] int GetPyramidRowOfDisk()const { return m_PyramidRow; }
private:
	void SetPositionOfDisk();
	const int m_PyramidRow;
	const Transform::Side m_PyramidSide;
};
