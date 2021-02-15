#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "TransformComponent.h"

dae::RenderComponent::RenderComponent(const std::string& filename)
	:BaseComponent(componentType::render), m_Texture(ResourceManager::GetInstance().LoadTexture(filename))
{}

dae::RenderComponent::RenderComponent(std::shared_ptr<Texture2D> texture)
	: BaseComponent(componentType::render), m_Texture(texture)
{}

void dae::RenderComponent::Render()const
{
	const auto pos {m_pGameObject->GetComponent<TransformComponent>()->GetPosition()};
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::RenderComponent::UpdateTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}