#include "MiniginPCH.h"
#include "GameObject.h"
#include <algorithm>
#include <functional>

#include "RenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "FpsComponent.h"
#include "AnimationComponent.h"
dae::GameObject::~GameObject()
{
	for (auto comp : m_pComponents)
		delete comp;
	m_pComponents.clear();
}

void dae::GameObject::Update()
{
	for (auto& comp : m_pComponents)
		comp->Update();
}

void dae::GameObject::Render() const
{
	for (const auto& comp : m_pComponents)
		comp->Render();
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	switch (component->m_ComponentType)
	{
	case BaseComponent::componentType::render:
	case BaseComponent::componentType::text:
	case BaseComponent::componentType::animation:
		m_NeedsToBeRendered = true;
		break;
	default:
		break;
	}
	component->SetGameObject(this);
	m_pComponents.push_back(component);
}

