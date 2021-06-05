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

class GameOverUI final :public UI_Comp
{
public:
	GameOverUI() = default;
	~GameOverUI() = default;
	GameOverUI(const GameOverUI& other) = delete;
	GameOverUI(GameOverUI&& other) noexcept = delete;
	GameOverUI& operator=(const GameOverUI& other) = delete;
	GameOverUI& operator=(GameOverUI&& other) noexcept = delete;

	void Update() override;
};

class WinUI final :public UI_Comp
{
public:
	WinUI() = default;
	~WinUI() = default;
	WinUI(const WinUI& other) = delete;
	WinUI(WinUI&& other) noexcept = delete;
	WinUI& operator=(const WinUI& other) = delete;
	WinUI& operator=(WinUI&& other) noexcept = delete;

	void Update() override;
};