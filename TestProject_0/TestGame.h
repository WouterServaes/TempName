#pragma once
#include "Minigin.h"
class TestGame: public dae::Minigin
{
public:
	TestGame() = default;
	~TestGame() override = default;
	TestGame(const TestGame& other) = delete;
	TestGame(TestGame&& other) noexcept = delete;
	TestGame& operator=(const TestGame& other) = delete;
	TestGame& operator=(TestGame&& other) noexcept = delete;

protected:
	void LoadGame() override;
};

