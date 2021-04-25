#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager() = default;
		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) noexcept = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) noexcept = delete;
		
		void AddScene(std::shared_ptr<Scene> pScene);
		void Update() const;
		void Render() const;
		void LoadScene(int sceneNr);
		void LoadScene(const std::string& sceneName);
		std::shared_ptr<Scene>& GetCurrentScene() { return m_ActiveScene; };
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene{nullptr};
	};
}
