#include "MiniginPCH.h"
#include "GameObject.h"
#include <functional>


#include "Render_Comp.h"
#include "Scene.h"
#include "Transform_Comp.h"
#include "Subject.h"
dae::GameObject::GameObject(const wchar_t* pObjectName, Scene* pScene, const bool isSubject)
	:m_pObjectName(pObjectName), m_pCurrentScene(pScene), m_pSubject((isSubject) ? new Subject() : nullptr)
{
	m_pComponents.push_back(new Transform_Comp(0.f, 0.f, 0.f));
	m_pComponents.at(0)->SetGameObject(this);
}

dae::GameObject::~GameObject()
{
	for (auto comp : m_pComponents)
		delete comp;
	m_pComponents.clear();

	if (m_pSubject)
		delete m_pSubject;
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

void dae::GameObject::Start()
{
	for (auto& comp : m_pComponents)
		comp->Start();
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	if (!m_NeedsToBeRendered)
	{

		if (typeid(*component) == typeid(Render_Comp))
			m_NeedsToBeRendered = true;
	}
	component->SetGameObject(this);
	m_pComponents.push_back(component);
}

dae::Transform_Comp* dae::GameObject::GetTransformComponent()
{
	{return GetComponent<Transform_Comp>(); }
}

dae::Subject* dae::GameObject::GetSubject() const
{
	return m_pSubject;
}

dae::Scene* dae::GameObject::GetCurrentScene() const
{
	return m_pCurrentScene;
}

dae::GameObject* dae::GameObject::GetGameObject(const wchar_t* pGameObjectName)
{
	return m_pCurrentScene->GetGameObject(pGameObjectName).get();
}

