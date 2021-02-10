#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	std::vector<std::shared_ptr<SceneObject>> objectsToDelete{};
	for(auto& object : m_Objects)
	{
		object->Update();
		if (object->IsMarkedForDeletion())
			objectsToDelete.push_back(object);
	}

	for (auto& objToDelete : objectsToDelete)
		objToDelete.reset();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

