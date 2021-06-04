#pragma once
#include <UI_Comp.h>
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

