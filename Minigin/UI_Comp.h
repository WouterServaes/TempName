#pragma once
#include "BaseComponent.h"

class Transform;

/// <summary>
/// UI components are used for ImGui elements, defined in the Update of the component
/// </summary>
class UI_Comp : public BaseComponent
{
public:
	UI_Comp() = default;
	~UI_Comp() = default;

	UI_Comp(const UI_Comp& other) = delete;
	UI_Comp(UI_Comp&& other) noexcept = delete;
	UI_Comp& operator=(const UI_Comp& other) = delete;
	UI_Comp& operator=(UI_Comp&& other) noexcept = delete;

	/// <summary>
	/// Defines the ImGui elements
	/// </summary>
	void Update() override = 0;

	/// <summary>
	/// Saves the Transform of the game object for ease of access
	/// </summary>
	void Start() override;
protected:
	const Transform* m_pTransform{ nullptr };
};

/// <summary>
/// Simple fps counter ui element
/// </summary>
class FpsUI final :public UI_Comp
{
public:
	FpsUI() = default;
	~FpsUI() = default;
	FpsUI(const FpsUI& other) = delete;
	FpsUI(FpsUI&& other) noexcept = delete;
	FpsUI& operator=(const FpsUI& other) = delete;
	FpsUI& operator=(FpsUI&& other) noexcept = delete;
	
	void Update() override;
};
