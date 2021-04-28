#include "MiniginPCH.h"
#include "GameObject.h"
#include <functional>

#include "Render_Comp.h"
#include "Scene.h"
#include "Transform_Comp.h"
#include "Subject.h"
GameObject::GameObject(const wchar_t* pObjectName, Scene* pScene, const bool isSubject)
	:m_pObjectName(pObjectName), m_pCurrentScene(pScene), m_pSubject((isSubject) ? new Subject() : nullptr)
{
	m_pComponents.push_back(new Transform_Comp(0.f, 0.f, 0.f));
	m_pComponents.at(0)->SetGameObject(this);
}

GameObject::~GameObject()
{
	for (auto comp : m_pComponents)
		delete comp;
	m_pComponents.clear();

	delete m_pSubject;
}

void GameObject::Update()
{
	if (!m_IsActive) return;
	for (auto& comp : m_pComponents)
		comp->Update();
}

void GameObject::Render() const
{
	if (!m_IsActive) return;

	for (const auto& comp : m_pComponents)
		comp->Render();
}

void GameObject::Start()
{
	for (auto& comp : m_pComponents)
		comp->Start();
}

void GameObject::AddComponent(BaseComponent* component)
{
	if (!m_NeedsToBeRendered)
	{
		if (typeid(*component) == typeid(Render_Comp))
			m_NeedsToBeRendered = true;
	}
	component->SetGameObject(this);
	m_pComponents.push_back(component);
}

Transform_Comp* GameObject::GetTransformComponent()
{
	{return GetComponent<Transform_Comp>(); }
}

Subject* GameObject::GetSubject() const
{
	return m_pSubject;
}

Scene* GameObject::GetCurrentScene() const
{
	return m_pCurrentScene;
}

GameObject* GameObject::GetGameObject(const wchar_t* pGameObjectName) const
{
	return m_pCurrentScene->GetGameObject(pGameObjectName).get();
}