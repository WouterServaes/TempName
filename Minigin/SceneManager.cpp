#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
void dae::SceneManager::Update() const
{
	m_ActiveScene->Update();
}

void dae::SceneManager::Render() const
{
	m_ActiveScene->Render();
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> pScene)
{
	if (m_ActiveScene == nullptr)
		m_ActiveScene = pScene;

	m_Scenes.push_back(pScene);
}

void dae::SceneManager::LoadScene(int sceneNr)
{
	if (sceneNr >= static_cast<int>(m_Scenes.size()))
	{
		const auto exceptionText{ "SceneManager::LoadScene(int) => sceneNr out of bounds, there's only " + std::to_string(m_Scenes.size()) + " scenes!" };
		throw(std::exception(exceptionText.c_str()));
	}

	m_ActiveScene = m_Scenes[sceneNr];
}

void dae::SceneManager::LoadScene(const std::string& sceneName)
{
	const auto foundScene{ std::find_if(m_Scenes.begin(), m_Scenes.end(), [&sceneName](const std::shared_ptr<Scene>& s)
		{
			return s->Name() == sceneName;
		}) };

	if (foundScene != m_Scenes.end())
	{
		m_ActiveScene = *foundScene;
	}
	else
	{
		//scene doesn't exit
		const auto exceptionText{ "SceneManager::LoadScene(const std::string&) => no scene with name \"" + sceneName + "\n found!" };
		throw(std::exception(exceptionText.c_str()));
	}
}