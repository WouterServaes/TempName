#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(){}

void dae::GameObject::Render() const
{
	if (m_RenderComp != nullptr) m_RenderComp->Render(m_Transform.GetPosition());
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddRenderComponent(const std::string& textureFileName)
{
	m_RenderComp = std::make_unique<RenderComponent>(textureFileName);
}
