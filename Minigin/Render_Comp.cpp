#include "MiniginPCH.h"
#include "Render_Comp.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"
#include "Transform_Comp.h"

dae::Render_Comp::Render_Comp(const std::string& filename)
{
	UpdateTexture(ResourceManager::GetInstance().LoadTexture(filename));
}

dae::Render_Comp::Render_Comp(const std::shared_ptr<Texture2D> texture)
{
	UpdateTexture(texture);
}

void dae::Render_Comp::Render()const
{
	const auto pos{ m_pGameObject->GetComponent<Transform_Comp>()->GetTransform()->GetPosition() };
	switch (m_Method)
	{
	case Method::Resize:
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_DstWidth, m_DstHeight);
		break;
	case Method::CutOut:
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_SrcX, m_SrcY, m_SrcWidth, m_SrcHeight);
		break;
	case Method::CutOutResize:
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_DstWidth, m_DstHeight, m_SrcX, m_SrcY, m_SrcWidth, m_SrcHeight);
		break;
	default:
		break;
	}
}

void dae::Render_Comp::UpdateTexture(const std::shared_ptr<Texture2D> texture, const  float dstWidth, const float dstHeight)
{
	if (dstWidth < 0)
		m_DstWidth = texture->GetTextureData().Dimensions.x;
	else
		m_DstWidth = dstWidth;

	if (dstHeight < 0)
		m_DstHeight = texture->GetTextureData().Dimensions.y;
	else
		m_DstHeight = dstHeight;

	m_Texture = texture;
	m_Method = Method::Resize;
}

void dae::Render_Comp::UpdateTexture(const std::shared_ptr<Texture2D> texture, const  float srcX, const float srcY, const float srcWidth,
	float srcHeight)
{
	m_SrcX = srcX;
	m_SrcY = srcY;
	m_SrcWidth = srcWidth;
	m_SrcHeight = srcHeight;

	m_Texture = texture;

	m_Method = Method::CutOut;
}

void dae::Render_Comp::UpdateTexture(const std::shared_ptr<Texture2D> texture, const  float dstWidth, const  float dstHeight,
	const float srcX, const  float srcY, const  float srcWidth, const float srcHeight)
{
	m_DstWidth = dstWidth;
	m_DstHeight = dstHeight;
	m_SrcX = srcX;
	m_SrcY = srcY;
	m_SrcWidth = srcWidth;
	m_SrcHeight = srcHeight;

	m_Texture = texture;

	m_Method = Method::CutOutResize;
}