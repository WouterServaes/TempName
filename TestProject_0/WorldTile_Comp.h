#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class Texture2D;
class Render_Comp;
class WorldTile_Comp final :public BaseComponent
{
public:
	WorldTile_Comp(std::shared_ptr<Texture2D> pNormalTexture, std::shared_ptr<Texture2D> pHighlightTexture, std::shared_ptr<Texture2D> pIntermediateTexture, glm::vec2 standLocation);
	~WorldTile_Comp() = default;
	WorldTile_Comp(const WorldTile_Comp& other) = delete;
	WorldTile_Comp(WorldTile_Comp&& other) noexcept = delete;
	WorldTile_Comp& operator=(const WorldTile_Comp& other) = delete;
	WorldTile_Comp& operator=(WorldTile_Comp&& other) noexcept = delete;
	void Start() override;

	void ToggleNormalHighlightedTexture();
	/// <summary>
	/// Sets the texture back to normal if highlighted
	/// </summary>
	void ToNormalTexture();

	/// <summary>
	/// Sets the texture highlighted if normal
	/// </summary>
	void ToHighlightedTexture();

	void ToIntermediateTexture();

	void RevertTextureChange();
	[[nodiscard]] glm::vec2 GetStandPos() const { return m_StandPosition; }
	[[nodiscard]] bool GetIsHighlighted() const { return m_TileLevel == TileLevel::Highlighted; }
	[[nodiscard]] bool GetIsIntermediate() const { return m_TileLevel == TileLevel::Intermediate; }

	enum class TileLevel
	{
		Normal, Intermediate, Highlighted
	};
private:
	//vector 2 stand position -> middle of top square of hexagon
	glm::vec2 m_StandPosition{};
	std::shared_ptr<Texture2D> m_pNormalTexture{}
	, m_pHighlightTexture{}, m_pIntermediateTexture{};

	TileLevel m_TileLevel{ TileLevel::Normal };
	TileLevel m_PrevTileLevel{ TileLevel::Normal };
	Render_Comp* m_pRenderComp{ nullptr };
};
