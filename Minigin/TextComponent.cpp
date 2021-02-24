#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "ResourceManager.h"

dae::TextComponent::TextComponent(const std::string& text, const std::string& font, int fontSize, const glm::vec4& color)
	:m_Text(text), m_pFont(ResourceManager::GetInstance().LoadFont(font, unsigned(fontSize)))
	, m_Color(new SDL_Color{ Uint8(color.r), Uint8(color.g), Uint8(color.b), Uint8(color.a) })
	, BaseComponent(componentType::text)
{
}

dae::TextComponent::~TextComponent()
{
	delete m_Color;
}

void dae::TextComponent::UpdateText(const std::string& newText)
{
	m_Text = newText;

	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), *m_Color);
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
	m_pRenderComponent->UpdateTexture(std::make_shared<Texture2D>(texture));
}

void dae::TextComponent::Update()
{
	if (!m_IsInitialized) //Text doesn't need to be updated every frame.
	{
		m_pRenderComponent = m_pGameObject->GetComponent<RenderComponent>();
		InitializeText();
		m_IsInitialized = true;
	}
}

void dae::TextComponent::InitializeText() const
{
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), *m_Color);
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
	m_pRenderComponent->UpdateTexture(std::make_shared<Texture2D>(texture));
}