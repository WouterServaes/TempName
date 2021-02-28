#pragma once
namespace dae
{
	class GameObject;
	class Commands
	{
	public:
		explicit Commands(std::shared_ptr<GameObject>& gameObject);
		Commands() = default;
		virtual ~Commands() = default;
		[[nodiscard]] bool IsActivated() const;
		virtual void SetActivated(bool activated);
		virtual void Execute() = 0;
	protected:
		bool m_Activated{ false };
		std::shared_ptr<GameObject> m_pGameObject{ nullptr };
	};

	class Command_QuitGame final :public Commands
	{
	public:
		explicit Command_QuitGame(bool* quitGame);
		void Execute() override;
	private:
		bool* m_pQuitGame;
	};

	class Command_RemoveHp final:public Commands
	{
	public:
		explicit Command_RemoveHp(std::shared_ptr<GameObject>& gameObject) :Commands(gameObject){};
		void Execute() override;
	};
}
