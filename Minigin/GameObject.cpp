#include "MiniginPCH.h"
#include "GameObject.h"

#include "Render_Comp.h"
#include "Scene.h"
#include "Transform_Comp.h"
#include "Subject.h"

GameObject::GameObject(const std::string& objectName, bool isSubject)
	:m_ObjectName(objectName), m_pCurrentScene(nullptr), m_pSubject((isSubject) ? new Subject() : nullptr)
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
	const auto comps{ static_cast<int>(m_pComponents.size()) };
	for (int idx{}; idx < comps; idx++)
		m_pComponents.at(idx)->Start();

}

void GameObject::AddComponent(BaseComponent* component)
{
	for (auto& comp : m_pComponents)
		if (typeid(*comp) == typeid(component))
		{
			Logger::LogWarning("GameObject::AddComponent() => can't add two of the same component to one game object!");
			return;
		}

	if (!m_NeedsToBeRendered)
	{
		if (typeid(*component) == typeid(Render_Comp))
			m_NeedsToBeRendered = true;
	}
	component->SetGameObject(this);
	m_pComponents.push_back(component);
}

Transform* GameObject::GetTransform()
{
	return GetComponent<Transform_Comp>()->GetTransform();
}

Subject* GameObject::GetSubject() const
{
	if (!m_pSubject)
		Logger::LogWarning("GameObject::GetSubject() => game object is not a subject!");
	
	return m_pSubject;
}

Scene* GameObject::GetCurrentScene() const
{
	return m_pCurrentScene;
}

void GameObject::SetScene(Scene* pScene, const bool warnIfFail)
{
	if (m_pCurrentScene == nullptr)
		m_pCurrentScene = pScene;
	else if(warnIfFail)
		Logger::LogWarning(("GameObject::SetScene: " + m_ObjectName + "already has a scene").c_str());
}

void GameObject::SetRenderLayer(const int layer)
{
	m_RenderLayer = layer;
}

int GameObject::GetRenderLayer() const
{
	return m_RenderLayer;
}

GameObject* GameObject::GetGameObject(const char* pGameObjectName) const
{
	return m_pCurrentScene->GetGameObject(pGameObjectName).get();
}
