#pragma once
#include "GameObject.h"
namespace dae
{
	class Scene
	{
	public:
		static int SceneCount;
		void AddGameObject(const std::shared_ptr<GameObject>& object);

		void Update();
		void Render() const;

		explicit Scene(const std::string& name);
		virtual ~Scene() = default;
		
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::string m_Name;
	private: 
		virtual void InitializeScene() = 0;
	protected:
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		const int sceneNr;
	};

}
