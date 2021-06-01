#pragma once
#include "Commands.h"
class Command_RemoveHp final :public Commands
{
public:
	Command_RemoveHp() = delete;
	explicit Command_RemoveHp(GameObject* gameObject) :Commands(gameObject) {};
	~Command_RemoveHp() = default;
	Command_RemoveHp(const Command_RemoveHp& other) = delete;
	Command_RemoveHp(Command_RemoveHp&& other) noexcept = delete;
	Command_RemoveHp& operator=(const Command_RemoveHp& other) = delete;
	Command_RemoveHp& operator=(Command_RemoveHp&& other) noexcept = delete;
	void Execute() override;
};

class Command_ColorChanged final :public Commands
{
public:
	Command_ColorChanged() = delete;
	explicit Command_ColorChanged(GameObject* gameObject) :Commands(gameObject) {};
	~Command_ColorChanged() = default;
	Command_ColorChanged(const Command_ColorChanged& other) = delete;
	Command_ColorChanged(Command_ColorChanged&& other) noexcept = delete;
	Command_ColorChanged& operator=(const Command_ColorChanged& other) = delete;
	Command_ColorChanged& operator=(Command_ColorChanged&& other) noexcept = delete;
	void Execute() override;
};

class Command_DefeatedCoily final :public Commands
{
public:
	Command_DefeatedCoily() = delete;
	explicit Command_DefeatedCoily(GameObject* gameObject) :Commands(gameObject) {};
	~Command_DefeatedCoily() = default;
	Command_DefeatedCoily(const Command_DefeatedCoily& other) = delete;
	Command_DefeatedCoily(Command_DefeatedCoily&& other) noexcept = delete;
	Command_DefeatedCoily& operator=(const Command_DefeatedCoily& other) = delete;
	Command_DefeatedCoily& operator=(Command_DefeatedCoily&& other) noexcept = delete;

	void Execute() override;
};

class Command_CatchedSlickOrSam final :public Commands
{
public:
	Command_CatchedSlickOrSam() = delete;
	explicit Command_CatchedSlickOrSam(GameObject* gameObject) :Commands(gameObject) {};
	~Command_CatchedSlickOrSam() = default;
	Command_CatchedSlickOrSam(const Command_CatchedSlickOrSam& other) = delete;
	Command_CatchedSlickOrSam(Command_CatchedSlickOrSam&& other) noexcept = delete;
	Command_CatchedSlickOrSam& operator=(const Command_CatchedSlickOrSam& other) = delete;
	Command_CatchedSlickOrSam& operator=(Command_CatchedSlickOrSam&& other) noexcept = delete;

	void Execute() override;
};

