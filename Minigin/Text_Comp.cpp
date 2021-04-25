#include "MiniginPCH.h"
#include "Text_Comp.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "ResourceManager.h"
dae::Text_Comp::Text_Comp(const std::string& text, const std::string& font,const int fontSize, const glm::vec4& color)
	:m_pFont(ResourceManager::GetInstance().LoadFont(font, unsigned(fontSize))), m_Text(text)
	, m_Color(new SDL_Color{ Uint8(color.r), Uint8(color.g), Uint8(color.b), Uint8(color.a) })

{
}

dae::Text_Comp::~Text_Comp()
{
	delete m_Color;
}

void dae::Text_Comp::Start()
{
	m_pRenderComponent = m_pGameObject->GetComponent<Render_Comp>();
	InitializeText();
}

void dae::Text_Comp::UpdateText(const std::string& newText)
{
	m_Text = newText;

	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), *m_Color);
	if (surf == nullptr)
	{
		Logger::LogError((static_cast<std::string>("Render text failed: ") + SDL_GetError()).c_str());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		Logger::LogError((static_cast<std::string>("Create text texture from surface failed: ") + SDL_GetError()).c_str());
	}
	SDL_FreeSurface(surf);
	m_pRenderComponent->UpdateTexture(std::make_shared<Texture2D>(texture));
}

void dae::Text_Comp::InitializeText() const
{
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), *m_Color);
	if (surf == nullptr)
	{
		Logger::LogError((static_cast<std::string>("Render text failed: ") + SDL_GetError()).c_str());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		Logger::LogError((static_cast<std::string>("Create text texture from surface failed: ") + SDL_GetError()).c_str());
	}
	SDL_FreeSurface(surf);
	m_pRenderComponent->UpdateTexture(std::make_shared<Texture2D>(texture));
}