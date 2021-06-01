#include "MiniginPCH.h"
#include "Scene.h"
#include <algorithm>
int Scene::SceneCount = 0;

Scene::Scene(const std::string& name)
	: m_Name{ name }, sceneNr{ SceneCount }
{
	SceneCount++;
}

void Scene::AddGameObject(const std::shared_ptr<GameObject>& object)
{
	if (!m_StartedScene)
		m_InitialStartObjIdxs.push_back(static_cast<int>(m_Objects.size()));
	else
		m_ObjIdxsNeedStart.push_back(static_cast<int>(m_Objects.size()));

	m_Objects.push_back(object);
}

void Scene::Update()
{
	if (!m_StartedScene)
		StartScene();

	StartLateObjects();

	for (auto& obj : m_Objects)
		obj->Update();

	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [](const std::shared_ptr<GameObject>& obj)
		{
			return obj->IsMarkedForDeletion();
		}), m_Objects.end());
}

void Scene::Render() const
{
	std::for_each(m_Objects.begin(), m_Objects.end(), [](const std::shared_ptr<GameObject>& obj)
		{
			if (obj->NeedsToBeRendered())
				obj->Render();
		});
}

void Scene::StartScene()
{
	m_StartedScene = true;

	for (int idx : m_InitialStartObjIdxs)
		m_Objects.at(idx)->Start();

	m_InitialStartObjIdxs.clear();
}

void Scene::StartLateObjects()
{
	if (m_ObjIdxsNeedStart.size() > 0)
	{
		for (int idx : m_ObjIdxsNeedStart)
			m_Objects.at(idx)->Start();
		m_ObjIdxsNeedStart.clear();
	}
}

std::shared_ptr< GameObject>& Scene::GetGameObject(const std::string& gameObjectName)
{
	for (auto& o : m_Objects)
		if (o->GetName() == gameObjectName)
			return o;

	Logger::LogError("GetGameObject(const std::string& pGameObjectName) no object with this name exist");
	return m_Objects[0];
}

std::shared_ptr< GameObject>& Scene::GetGameObject(const int idx)
{
	if (static_cast<int>(m_Objects.size()) < idx &&
		m_Objects.at(idx) != nullptr)
		return m_Objects.at(idx);

	Logger::LogError("GetGameObject(int idx) no object at this idx");
	return m_Objects[0];
}