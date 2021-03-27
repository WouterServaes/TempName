#include "MiniginPCH.h"
#include "Render_Comp.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"
#include "Transform_Comp.h"

dae::Render_Comp::Render_Comp(const std::string& filename)
	:m_Texture(ResourceManager::GetInstance().LoadTexture(filename))
{}

dae::Render_Comp::Render_Comp(std::shared_ptr<Texture2D> texture)
	: m_Texture(texture)
{}

void dae::Render_Comp::Render()const
{
	const auto pos{ m_pGameObject->GetComponent<Transform_Comp>()->GetTransform()->GetPosition() };
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::Render_Comp::UpdateTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}