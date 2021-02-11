#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "Texture2D.h"

dae::TextObject::TextObject(const std::string& text, const std::shared_ptr<Font>& font )
	: m_Text(text), m_Font(font), m_Texture(nullptr)
{
	m_NeedsToBeRendered = true;
}


void dae::TextObject::Update()
{	
	bool needsUpdate{ HandleComponents() };

	bool colorChanged{ false };
	if(m_pColoredTextComp != nullptr)
	{
		colorChanged = true;
		needsUpdate = true;
	}
	
	if (needsUpdate)
	{
		SDL_Color color = { 255, 255, 255 };
		if(colorChanged)
		{
			glm::vec4 tempColor{ m_pColoredTextComp->GetTextColor() };
			color = SDL_Color({ Uint8(tempColor.r), Uint8(tempColor.g), Uint8(tempColor.b), Uint8(tempColor.a) });
		}
		
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
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
		m_Texture = std::make_shared<Texture2D>(texture);
	}
}

void dae::TextObject::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::TextObject::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

bool dae::TextObject::HandleComponents()
{
	bool needsUpdate{ false };
	if (m_IsInitialized == false)
	{
		m_IsInitialized = true;
		needsUpdate =  true;
	}

	if (m_pChangeableTextComp != nullptr && m_pChangeableTextComp->GetNeedsUpdate())
	{
		m_Text = m_pChangeableTextComp->GetNewText();

		needsUpdate = true;
	}

	if (m_pFpsCounterComp != nullptr)
	{
		m_pFpsCounterComp->UpdateFpsCounter();
		m_Text = m_pFpsCounterComp->GetNewText();
		needsUpdate = true;
	}

	return needsUpdate;
}

void dae::TextObject::AddChangleableTextComponent()
{
	m_pChangeableTextComp = std::make_unique<ChangeableTextComponent>();
}

void dae::TextObject::AddColoredTextComponent(const glm::vec4& color)
{
	m_pColoredTextComp = std::make_unique<ColoredTextComponent>(color);
}

void dae::TextObject::AddFpsCounterComponent()
{
	m_pFpsCounterComp = std::make_unique<FpsCounterComponent>();
}
