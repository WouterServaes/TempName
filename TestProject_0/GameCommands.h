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

class Command_MoveLeftUp final : public Commands
{
public:
	Command_MoveLeftUp() = delete;
	explicit Command_MoveLeftUp(GameObject* gameObject) :Commands(gameObject) {};
	~Command_MoveLeftUp() = default;
	Command_MoveLeftUp(const Command_MoveLeftUp& other) = delete;
	Command_MoveLeftUp(Command_MoveLeftUp&& other) noexcept = delete;
	Command_MoveLeftUp& operator=(const Command_MoveLeftUp& other) = delete;
	Command_MoveLeftUp& operator=(Command_MoveLeftUp&& other) noexcept = delete;

	void Execute() override;
};

class Command_MoveLeftDown final : public Commands
{
public:
	Command_MoveLeftDown() = delete;
	explicit Command_MoveLeftDown(GameObject* gameObject) :Commands(gameObject) {};
	~Command_MoveLeftDown() = default;
	Command_MoveLeftDown(const Command_MoveLeftDown& other) = delete;
	Command_MoveLeftDown(Command_MoveLeftDown&& other) noexcept = delete;
	Command_MoveLeftDown& operator=(const Command_MoveLeftDown& other) = delete;
	Command_MoveLeftDown& operator=(Command_MoveLeftDown&& other) noexcept = delete;

	void Execute() override;
};

class Command_MoveRightUp final : public Commands
{
public:
	Command_MoveRightUp() = delete;
	explicit Command_MoveRightUp(GameObject* gameObject) :Commands(gameObject) {};
	~Command_MoveRightUp() = default;
	Command_MoveRightUp(const Command_MoveRightUp& other) = delete;
	Command_MoveRightUp(Command_MoveRightUp&& other) noexcept = delete;
	Command_MoveRightUp& operator=(const Command_MoveRightUp& other) = delete;
	Command_MoveRightUp& operator=(Command_MoveRightUp&& other) noexcept = delete;

	void Execute() override;
};

class Command_MoveRightDown final : public Commands
{
public:
	Command_MoveRightDown() = delete;
	explicit Command_MoveRightDown(GameObject* gameObject) :Commands(gameObject) {};
	~Command_MoveRightDown() = default;
	Command_MoveRightDown(const Command_MoveRightDown& other) = delete;
	Command_MoveRightDown(Command_MoveRightDown&& other) noexcept = delete;
	Command_MoveRightDown& operator=(const Command_MoveRightDown& other) = delete;
	Command_MoveRightDown& operator=(Command_MoveRightDown&& other) noexcept = delete;

	void Execute() override;
};