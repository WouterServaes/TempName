#pragma once
#include <BaseComponent.h>
class WorldTile_Comp;

class WorldTileManager_Comp final:public BaseComponent
{
public:
	WorldTileManager_Comp(std::shared_ptr<Texture2D> pNormalTexture, std::shared_ptr<Texture2D> pHighlightTexture, float tileWidth,float tileSmallestHeight,  int bottomRowAmount = 5);
	~WorldTileManager_Comp() = default;
	WorldTileManager_Comp(const WorldTileManager_Comp& other) = delete;
	WorldTileManager_Comp(WorldTileManager_Comp&& other) noexcept = delete;
	WorldTileManager_Comp& operator=(const WorldTileManager_Comp& other) = delete;
	WorldTileManager_Comp& operator=(WorldTileManager_Comp&& other) noexcept = delete;

	void Start() override;

	/// <summary>
	/// Resets all the tiles
	/// </summary>
	void ResetTiles();
private:
	void SpawnTiles();
	
	const int m_BottomRowAmount;
	const float m_TileWidth, m_TileSmallestHeight;
	std::vector<WorldTile_Comp*> m_pWorldTiles{nullptr};

	std::shared_ptr<Texture2D> m_pNormalTexture
	                           , m_pHighlightTexture;
};

