#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		Logger::LogError((static_cast<std::string>("Failed to load support for png's: ") + SDL_GetError()).c_str());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
	{
		Logger::LogError((static_cast<std::string>("Failed to load support for jpg's: ") + SDL_GetError()).c_str());
	}

	if (TTF_Init() != 0)
	{
		Logger::LogError((static_cast<std::string>("Failed to load support for fonts: ") + SDL_GetError()).c_str());
	}
}

std::shared_ptr< Texture2D> ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		Logger::LogError((static_cast<std::string>("Failed to load texture: ") + SDL_GetError()).c_str());
	}
	return std::make_shared<Texture2D>(texture, file);
}

std::shared_ptr< Font> ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + file, size);
}