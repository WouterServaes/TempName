#pragma once

class GameObject;
class Commands
{
public:
	Commands() = default;
	explicit Commands(GameObject* gameObject);
	virtual ~Commands() = default;
	Commands(const Commands& other) = delete;
	Commands(Commands&& other) noexcept = delete;
	Commands& operator=(const Commands& other) = delete;
	Commands& operator=(Commands&& other) noexcept = delete;

	///Returns true if the Command is activated, used in InputManager
	[[nodiscard]] bool IsActivated() const;

	/// <summary>
	/// Sets the command to active, used in InputManager
	/// </summary>
	virtual void SetActivated(bool activated);

	/// <summary>
	/// Executes the command
	/// </summary>
	virtual void Execute() = 0;
protected:
	bool m_Activated{ false };
	GameObject* m_pGameObject{ nullptr };
};

class Command_QuitGame final :public Commands
{
public:
	Command_QuitGame() = delete;
	explicit Command_QuitGame(bool* quitGame);
	~Command_QuitGame() = default;
	Command_QuitGame(const Command_QuitGame& other) = delete;
	Command_QuitGame(Command_QuitGame&& other) noexcept = delete;
	Command_QuitGame& operator=(const Command_QuitGame& other) = delete;
	Command_QuitGame& operator=(Command_QuitGame&& other) noexcept = delete;
	void Execute() override;
private:
	bool* m_pQuitGame;
};
