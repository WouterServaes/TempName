#include "MiniginPCH.h"
#include "GameObject.h"
#include <algorithm>
#include "RenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "FpsComponent.h"
#include "AnimationComponent.h"
dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	if (m_UseTextCompToPrintFps)
		SetFirstTextCompToFps();

	for (auto& comp : m_pComponents)
		comp->Update();
}

void dae::GameObject::Render() const
{
	auto position{ GetPosition() };

	for (const auto& comp : m_pComponents)
		comp->Render(position);
}

void dae::GameObject::AddComponent(std::unique_ptr<BaseComponent> component)
{
	switch (component->m_ComponentType)
	{
	case BaseComponent::componentType::render:
	case BaseComponent::componentType::text:
	case BaseComponent::componentType::animation:
		m_NeedsToBeRendered = true;
		break;
	case BaseComponent::componentType::fps:
		m_UseTextCompToPrintFps = dynamic_cast<const FpsComponent*>(component.get())->UseTextCompToPrint();
		break;
	default:
		break;
	}

	
	component->SetGameObject(this);
	m_pComponents.push_back(std::move(component));
}

int dae::GameObject::GetFps() const
{
	const auto it{ std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const std::unique_ptr<BaseComponent>& comp)
		{
			return comp->m_ComponentType == BaseComponent::componentType::fps;
		}) };

	if (it != m_pComponents.end())
		return dynamic_cast<const FpsComponent*>(it->get())->GetFps();

	throw(std::runtime_error(std::string("Accessing FPS failed: no FpsComponent on this GameObject")));
}

void dae::GameObject::SetFirstTextCompToFps()
{
	const auto firstTextIt{ std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const std::unique_ptr<BaseComponent>& comp)
		{
			return comp->m_ComponentType == BaseComponent::componentType::text;
		}) };
	if (firstTextIt == m_pComponents.end())
		throw(std::runtime_error(std::string("Printing fps failed -> no TextComponent on this GameObject")));
	dynamic_cast<TextComponent*>(firstTextIt->get())->UpdateText("FPS:" + std::string(std::to_string(GetFps())));
}

glm::vec3 dae::GameObject::GetPosition() const
{
	const auto it{ std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const std::unique_ptr<BaseComponent>& comp)
		{
			return comp->m_ComponentType == BaseComponent::componentType::transform;
		}) };

	if (it != m_pComponents.end())
		return dynamic_cast<const TransformComponent*>(it->get())->GetPosition();

	return { 0.f, 0.f, 0.f };
}

std::unique_ptr<dae::BaseComponent>::pointer dae::GameObject::GetComponent(BaseComponent::componentType type)
{
	auto it{ std::find_if(m_pComponents.begin(), m_pComponents.end(), [type](const std::unique_ptr<BaseComponent>& comp)
		{
			return comp->m_ComponentType == type;
		}) };

	if (it != m_pComponents.end())
		return it->get();
	
	throw(std::runtime_error(std::string("GetComponent(type) -> Component doesn't exist on GameObject")));
	
}