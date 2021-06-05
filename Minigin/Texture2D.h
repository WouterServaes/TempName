#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#define SDL_MAIN_HANDLED
#include <SDL.h>

class Texture2D
{
public:
	struct TextureData
	{
		glm::vec2 Dimensions{};
		UINT32 Format{};
		int TextureAccess{};
		std::string FileName{};
	};

	Texture2D() = delete;
	explicit Texture2D(SDL_Texture* texture, const std::string& fileName);
	~Texture2D();

	Texture2D(const Texture2D&) = delete;
	Texture2D(Texture2D&&) = delete;
	Texture2D& operator= (const Texture2D&) = delete;
	Texture2D& operator= (const Texture2D&&) = delete;

	[[nodiscard]] SDL_Texture* GetSDLTexture() const;
	[[nodiscard]] const TextureData& GetTextureData() const { return m_TextureData; }
private:
	SDL_Texture* m_Texture;
	TextureData m_TextureData{};
};
