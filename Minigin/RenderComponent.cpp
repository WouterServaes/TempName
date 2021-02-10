#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(const std::string& filename)
	:m_Texture(ResourceManager::GetInstance().LoadTexture(filename))
{}

void dae::RenderComponent::Render(const glm::vec3& renderPos)const
{
	Renderer::GetInstance().RenderTexture(*m_Texture, renderPos.x, renderPos.y);
}