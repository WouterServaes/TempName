#include "MiniginPCH.h"
#include "GameObject.h"
#include <algorithm>
#include "RenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(){}

void dae::GameObject::Render() const
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](const std::unique_ptr<BaseComponent>& comp)
		{
			switch (comp->m_ComponentType)
			{
			case BaseComponent::componentType::render:
				dynamic_cast<const RenderComponent*>(comp.get())->Render(GetPosition());
				break;
			case BaseComponent::componentType::text:
				dynamic_cast<const TextComponent*>(comp.get())->RenderText(GetPosition());
				break;

			}
		});
}

glm::vec3 dae::GameObject::GetPosition() const 
{
	const auto it{ std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const std::unique_ptr<BaseComponent>& comp)
		{
			return comp->m_ComponentType == BaseComponent::componentType::transform;
		}) };

	if (it != m_pComponents.end())
		return dynamic_cast<const TransformComponent*>(it->get())->GetPosition();
	else
		return { 0.f, 0.f, 0.f };
}

void dae::GameObject::AddComponent(std::unique_ptr<BaseComponent> component)
{
	
	if (!m_NeedsToBeRendered && 
		(dynamic_cast<const RenderComponent*>(component.get()) != nullptr ||
		dynamic_cast<const TextComponent*>(component.get()) != nullptr))
	{
		m_NeedsToBeRendered = true;
	}	
	m_pComponents.push_back(std::move(component));
}