#pragma once
namespace dae
{
	class GameObject;
	class Commands
	{
	public:
		explicit Commands(GameObject* gameObject);
		Commands() = default;
		virtual ~Commands() = default;
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
		explicit Command_QuitGame(bool* quitGame);
		void Execute() override;
	private:
		bool* m_pQuitGame;
	};

	class Command_RemoveHp final :public Commands
	{
	public:
		explicit Command_RemoveHp(GameObject* gameObject) :Commands(gameObject) {};
		void Execute() override;
	};

	class Command_ColorChanged final :public Commands
	{
	public:
		explicit Command_ColorChanged(GameObject* gameObject) :Commands(gameObject) {};
		void Execute() override;
	};

	class Command_DefeatedCoily final :public Commands
	{
	public:
		explicit Command_DefeatedCoily(GameObject* gameObject) :Commands(gameObject) {};
		void Execute() override;
	};

	class Command_CatchedSlickOrSam final :public Commands
	{
	public:
		explicit Command_CatchedSlickOrSam(GameObject* gameObject) :Commands(gameObject) {};
		void Execute() override;
	};
}
