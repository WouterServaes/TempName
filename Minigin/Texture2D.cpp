#include "MiniginPCH.h"
#include "Texture2D.h"


dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
	int width{}, height{};
	SDL_QueryTexture(m_Texture, &m_TextureData.Format, &m_TextureData.TextureAccess, &width, &height);
	m_TextureData.Dimensions.x = static_cast<float>(width);
	m_TextureData.Dimensions.y = static_cast<float>(height);
}

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}


