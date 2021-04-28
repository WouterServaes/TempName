#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "Font.h"
TTF_Font* Font::GetFont() const {
	return m_Font;
}

Font::Font(const std::string& fullPath, unsigned int size) : m_Font(nullptr), m_Size(size)
{
	m_Font = TTF_OpenFont(fullPath.c_str(), size);

	if (m_Font == nullptr)
		Logger::LogError((static_cast<std::string>("Failed to load font: ") + SDL_GetError()).c_str());
}

Font::~Font()
{
	TTF_CloseFont(m_Font);
}