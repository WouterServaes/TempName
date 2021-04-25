#include "MiniginPCH.h"
#include "Scene.h"
#include <algorithm>
#include "Logger.h"
int dae::Scene::SceneCount = 0;

dae::Scene::Scene(const std::string& name)
	: m_Name{name}, sceneNr{ SceneCount }
{
	SceneCount++;
}

void dae::Scene::AddGameObject(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void dae::Scene::Update()
{
	if(!m_StartedScene)
		StartScene();
	
	for (auto& obj : m_Objects)
		obj->Update();

	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [](const std::shared_ptr<GameObject>& obj)
		{
			return obj->IsMarkedForDeletion();
		}), m_Objects.end());
}

void dae::Scene::Render() const
{
	std::for_each(m_Objects.begin(), m_Objects.end(), [](const std::shared_ptr<GameObject>& obj)
		{
			if (obj->NeedsToBeRendered())
				obj->Render();
		});
}

void dae::Scene::StartScene()
{
	m_StartedScene = true;
	for (auto& obj : m_Objects)
		obj->Start();
}

std::shared_ptr<dae::GameObject>& dae::Scene::GetGameObject(const wchar_t* pGameObjectName)
{
	for (auto& o : m_Objects)
		if (o->GetName() == pGameObjectName)
			return o;

	Logger::LogError("GetGameObject(const wchar_t* pGameObjectName) no object with this name exist");
	return m_Objects[0];
}

std::shared_ptr<dae::GameObject>& dae::Scene::GetGameObject(const int idx)
{
	if (static_cast<int>(m_Objects.size()) < idx &&
		m_Objects.at(idx) != nullptr)
		return m_Objects.at(idx);

	Logger::LogError("GetGameObject(int idx) no object at this idx");
	return m_Objects[0];
}