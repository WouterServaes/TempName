#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
void dae::SceneManager::Update()
{
	m_ActiveScene->Update();
//	for (auto& scene : m_Scenes)
//	{
//		scene->Update();
//	}
}

void dae::SceneManager::Render()
{
	m_ActiveScene->Render();
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	if (m_ActiveScene == nullptr)
		m_ActiveScene = scene;
	
	m_Scenes.push_back(scene);
}

void dae::SceneManager::LoadScene(int sceneNr)
{
	if(sceneNr>=m_Scenes.size())
	{
		//scene doesn't exist;
		
	}

	m_ActiveScene = m_Scenes[sceneNr];
}

void dae::SceneManager::LoadScene(const std::string& sceneName)
{
	const auto foundScene{ std::find_if(m_Scenes.begin(), m_Scenes.end(), [&sceneName](const std::shared_ptr<Scene>& s)
	{
			return s->m_Name == sceneName;
	}) };
	
	if(foundScene!=m_Scenes.end())
	{
		//found scene
		m_ActiveScene = *foundScene;
	}

	//scene doesn't exit
}