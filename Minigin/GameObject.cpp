#include "MiniginPCH.h"
#include "GameObject.h"
#include <functional>
#include "TransformComponent.h"
#include "Subject.h"
dae::GameObject::GameObject(const wchar_t* pObjectName,const bool isSubject)
	:m_pObjectName(pObjectName)
{
	m_pComponents.push_back(new TransformComponent(0.f, 0.f, 0.f));
	if(isSubject)
	{
		m_pSubject = new Subject();
	}
}

dae::GameObject::~GameObject()
{
	
	for (auto comp : m_pComponents)
		delete comp;
	m_pComponents.clear();

	delete m_pObjectName;
}

void dae::GameObject::Update()
{
	if (!m_IsActive) return;
	for (auto& comp : m_pComponents)
		comp->Update();
}

void dae::GameObject::Render() const
{
	if (!m_IsActive) return;

	for (const auto& comp : m_pComponents)
		comp->Render();
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	if (!m_NeedsToBeRendered)
	{
		if (component->componentType == BaseComponent::componentType::render)
			m_NeedsToBeRendered = true;
	}
	component->SetGameObject(this);
	m_pComponents.push_back(component);
}

dae::TransformComponent* dae::GameObject::GetTransformComponent()
{
	{return GetComponent<TransformComponent>(); }
}

dae::Subject* dae::GameObject::GetSubject() const
{
	return m_pSubject;
}

