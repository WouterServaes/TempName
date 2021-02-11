#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "ResourceManager.h"

dae::TextComponent::TextComponent(const std::string& text, const std::string& font, int fontSize, const glm::vec4& color)
	:m_Text(text), m_pFont(ResourceManager::GetInstance().LoadFont(font, unsigned(fontSize))), m_Color(color)
{
	SDL_Color sdlColor = { Uint8(m_Color.r), Uint8(m_Color.g), Uint8(m_Color.b), Uint8(m_Color.a) };
	
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), sdlColor);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_pRenderComp = std::make_unique<RenderComponent>(std::make_shared<Texture2D>(texture));
	
}


void dae::TextComponent::UpdateText(const std::string& newText)
{
	m_Text = newText;

	SDL_Color sdlColor = { Uint8(m_Color.r), Uint8(m_Color.g), Uint8(m_Color.b), Uint8(m_Color.a) };
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), sdlColor);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);

	m_pRenderComp->UpdateTexture(std::make_shared<Texture2D>(texture));
}
