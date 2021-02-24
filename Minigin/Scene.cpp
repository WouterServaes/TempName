#include "MiniginPCH.h"
#include "Scene.h"
#include <algorithm>

int dae::Scene::SceneCount = 0;

dae::Scene::Scene(const std::string& name)
: m_Name(name), sceneNr{SceneCount}
{
	SceneCount++;
}

void dae::Scene::AddGameObject(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void dae::Scene::Update()
{	
	for(size_t idx{}; idx<m_Objects.size();++idx)
		m_Objects[idx]->Update();
		
	
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