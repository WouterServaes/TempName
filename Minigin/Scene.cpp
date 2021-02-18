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
	for(size_t idx{}; idx<m_Objects.size();++idx)
		m_Objects[idx]->Update();
		
	
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

