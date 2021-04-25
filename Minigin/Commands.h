#pragma once
namespace dae
{
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

		[[nodiscard]] bool IsActivated() const;
		virtual void SetActivated(bool activated);
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
}
