#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

class Texture2D;
/**
 * Simple RAII wrapper for the SDL renderer
 */
class Renderer final : public Singleton<Renderer>
{
public:
	~Renderer() = default;
	Renderer(const Renderer& other) = delete;
	Renderer(Renderer&& other) noexcept = delete;
	Renderer& operator=(const Renderer& other) = delete;
	Renderer& operator=(Renderer&& other) noexcept = delete;

	void Init(SDL_Window* window);
	void Render() const;
	void Destroy();

	/// <summary>
	/// Renders a full texture at x, y with original width and height
	/// </summary>
	/// <param name="texture">original texture</param>
	/// <param name="x">x position of rendered texture</param>
	/// <param name="y">y position of rendered texture</param>
	void RenderTexture(const Texture2D& texture, float x, float y) const;

	/// <summary>
	/// Renders a full texture at x, y with width and height
	/// </summary>
	/// <param name="texture">original texture</param>
	/// <param name="x">x position of rendered texture</param>
	/// <param name="y">y position of rendered texture</param>
	/// <param name="width">width of rendered texture</param>
	/// <param name="height">height of rendered texture</param>
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

	/// <summary>
	/// Renders a cut texture at dstX, dstY with original texture width and height
	/// texture is cut from texture with srcX, srcY, srcWidth and srcHeight
	/// </summary>
	/// <param name="texture">original texture</param>
	/// <param name="x">x position of rendered texture</param>
	/// <param name="y">y position of rendered texture</param>
	/// <param name="srcX">bottomLeft x of cut-out part</param>
	/// <param name="srcY">bottomLeft y of cut-out part</param>
	/// <param name="srcWidth">Width of cut-out part</param>
	/// <param name="srcHeight">height of cut-out part></param>
	void RenderTexture(const Texture2D& texture, float x, float y, float srcX, float srcY, float srcWidth, float srcHeight) const;

	/// <summary>
	/// Renders a cut texture at dstX, dstY with dstWidth and dstHeight
	/// texture is cut from texture with srcX, srcY, srcWidth and srcHeight
	/// </summary>
	/// <param name="texture">original texture</param>
	/// <param name="dstX">x position of rendered texture</param>
	/// <param name="dstY">y position of rendered texture</param>
	/// <param name="dstWidth">width of rendered texture</param>
	/// <param name="dstHeight">height of rendered texture</param>
	/// <param name="srcX">bottomLeft x of cut-out part</param>
	/// <param name="srcY">bottomLeft y of cut-out part</param>
	/// <param name="srcWidth">Width of cut-out part</param>
	/// <param name="srcHeight">height of cut-out part></param>
	void RenderTexture(const Texture2D& texture, float dstX, float dstY, float dstWidth, float dstHeight, float srcX, float srcY, float srcWidth, float srcHeight) const;

	[[nodiscard]] SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
private:
	friend class Singleton<Renderer>;
	Renderer() = default;

	SDL_Renderer* m_Renderer{};
};
