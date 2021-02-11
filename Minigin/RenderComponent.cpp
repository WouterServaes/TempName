#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(const std::string& filename)
	:m_Texture(ResourceManager::GetInstance().LoadTexture(filename)), BaseComponent(componentType::render)
{}

dae::RenderComponent::RenderComponent(std::shared_ptr<Texture2D> texture)
	:m_Texture(texture), BaseComponent(componentType::render)
{}

void dae::RenderComponent::Render(const glm::vec3& renderPos)const
{
	Renderer::GetInstance().RenderTexture(*m_Texture, renderPos.x, renderPos.y);
}

void dae::RenderComponent::UpdateTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}