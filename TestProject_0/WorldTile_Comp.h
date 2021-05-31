#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

#include "Texture2D.h"
class WorldTile_Comp final:BaseComponent
{
public:
	WorldTile_Comp(std::shared_ptr<Texture2D> pNormalTexture, std::shared_ptr<Texture2D> pHighlightTexture, glm::vec2 standLocation);
	~WorldTile_Comp() = default;
	WorldTile_Comp(const WorldTile_Comp& other) = delete;
	WorldTile_Comp(WorldTile_Comp&& other) noexcept = delete;
	WorldTile_Comp& operator=(const WorldTile_Comp& other) = delete;
	WorldTile_Comp& operator=(WorldTile_Comp&& other) noexcept = delete;

	/// <summary>
	/// Swaps between the normal and highlighted texture
	/// </summary>
	void ChangeTexture();

	/// <summary>
	/// Sets the texture back to normal if highlighted
	/// </summary>
	void ToNormalTexture();
private:
	//vector 2 stand position -> middle of top square of hexagon
	glm::vec2 m_StandPosition{};
	
	
	bool m_IsHighlighted{ false };
	std::shared_ptr<Texture2D> m_pNormalTexture{}
	                           , m_pHighlightTexture{};
	
};

