#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(){}

void dae::GameObject::Render() const
{
	if (m_RenderComponent) m_RenderComponent->Render(m_Transform.GetPosition());
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddRenderComponent(const std::string& textureFileName)
{
	m_RenderComponent = std::make_unique<RenderComponent>(textureFileName);
}
