#pragma once
#include "Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	~SceneManager() = default;
	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) noexcept = delete;
	SceneManager& operator=(const SceneManager& other) = delete;
	SceneManager& operator=(SceneManager&& other) noexcept = delete;

	/// <summary>
	/// Adds a scene to the game
	/// </summary>
	void AddScene(std::shared_ptr<Scene> pScene);

	/// <summary>
	/// Calls Update() of the active scene
	/// </summary>
	void Update() const;

	/// <summary>
	/// Calls Render() of the active scene
	/// </summary>
	void Render() const;

	/// <summary>
	/// Returns a Scene on position "sceneNr" from the Scenes 
	/// </summary>
	void LoadScene(int sceneNr);

	/// <summary>
	/// Loads a scene using name of the scene
	/// </summary>
	void LoadScene(const std::string& sceneName);

	/// <summary>
	/// Returns the active scene
	/// </summary>
	std::shared_ptr<Scene>& GetCurrentScene() { return m_ActiveScene; };
private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_Scenes;
	std::shared_ptr<Scene> m_ActiveScene{ nullptr };
};
