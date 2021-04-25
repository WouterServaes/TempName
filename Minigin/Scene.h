#pragma once
#include "GameObject.h"
namespace dae
{
	class Scene
	{
	public:
		static int SceneCount;
		void AddGameObject(const std::shared_ptr<GameObject>& object);
		std::shared_ptr<GameObject>& GetGameObject(int idx);
		std::shared_ptr<GameObject>& GetGameObject(const wchar_t* pGameObjectName);
		void Update();
		void Render() const;
		[[nodiscard]] const std::string& Name() const { return m_Name; };
		explicit Scene(const std::string& name);
		virtual ~Scene() = default;
		
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		void StartScene();
		std::string m_Name;
		bool m_StartedScene = false;
		virtual void InitializeScene() = 0;
	protected:
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		const int sceneNr;
	};

}
