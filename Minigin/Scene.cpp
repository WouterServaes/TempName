#include "MiniginPCH.h"
#include "Scene.h"
#include <algorithm>
using namespace dae;

Scene::Scene(const std::string& name) : m_Name(name) {}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{	
	std::vector<std::shared_ptr<GameObject>> objectsToDelete{};
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
	std::for_each(m_Objects.begin(), m_Objects.end(), [](const std::shared_ptr<GameObject>& obj)
		{
			if (obj->NeedsToBeRendered())
				obj->Render();

		});
}

