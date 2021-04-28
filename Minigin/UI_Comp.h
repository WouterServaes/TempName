#pragma once
#include "BaseComponent.h"

class Transform_Comp;
class UI_Comp : public BaseComponent
{
public:

	UI_Comp() = default;
	~UI_Comp() = default;

	UI_Comp(const UI_Comp& other) = delete;
	UI_Comp(UI_Comp&& other) noexcept = delete;
	UI_Comp& operator=(const UI_Comp& other) = delete;
	UI_Comp& operator=(UI_Comp&& other) noexcept = delete;

	void Update() override = 0;
	void Start() override;
protected:
	const Transform_Comp* m_pTransformComponent{ nullptr };
};

class StartUI final :public UI_Comp
{
public:
	StartUI() = default;
	~StartUI() = default;
	StartUI(const StartUI& other) = delete;
	StartUI(StartUI&& other) noexcept = delete;
	StartUI& operator=(const StartUI& other) = delete;
	StartUI& operator=(StartUI&& other) noexcept = delete;

	void Update() override;
};

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
