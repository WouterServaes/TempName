#include "MiniginPCH.h"
#include "GameObject.h"
#include <algorithm>
#include "RenderComponent.h"
#include "TextComponent.h"
dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(){}

void dae::GameObject::Render() const
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](const std::unique_ptr<BaseComponent>& comp)
		{
			const auto renderComp{ dynamic_cast<const RenderComponent*>(comp.get()) };
			const auto textComp{ dynamic_cast<const TextComponent*>(comp.get()) };
		
			if (renderComp != nullptr)
				renderComp->Render(m_Transform.GetPosition());
			if (textComp != nullptr)
			{
				
				textComp->RenderText(m_Transform.GetPosition());
			}
		});
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}


void dae::GameObject::AddComponent(std::unique_ptr<BaseComponent> component)
{
	
	if (dynamic_cast<const RenderComponent*>(component.get()) != nullptr ||
		dynamic_cast<const TextComponent*>(component.get()) != nullptr)
	{
		
		m_NeedsToBeRendered = true;
	}
	
	m_pComponents.push_back(std::move(component));
}