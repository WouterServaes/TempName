#pragma once
#include <BaseComponent.h>
#pragma warning(push)
#pragma warning (disable:4201) //nonstandard extension used : nameless struct / union
#include <glm/vec2.hpp>
#pragma warning(pop)

class WorldTile_Comp;

class WorldTileManager_Comp final :public BaseComponent
{
public:
	WorldTileManager_Comp(std::shared_ptr<Texture2D> pNormalTexture, std::shared_ptr<Texture2D> pHighlightTexture, std::shared_ptr<Texture2D> pIntermediateTexture,
		int bottomRowAmount = 5);
	~WorldTileManager_Comp() = default;
	WorldTileManager_Comp(const WorldTileManager_Comp& other) = delete;
	WorldTileManager_Comp(WorldTileManager_Comp&& other) noexcept = delete;
	WorldTileManager_Comp& operator=(const WorldTileManager_Comp& other) = delete;
	WorldTileManager_Comp& operator=(WorldTileManager_Comp&& other) noexcept = delete;

	void Start() override;
	void Update() override;
	[[nodiscard]] glm::vec2 GetGridTileDimensions() const;
	/// <summary>
	/// Resets all the tiles
	/// </summary>
	void ResetTiles();

	[[nodiscard]] glm::vec2 GetTileStandPos(int tileIdx) const;
	[[nodiscard]] WorldTile_Comp* GetTileAtPosition(glm::vec2 position) const;
	[[nodiscard]] int GetTileIdxAtPosition(glm::vec2 position) const;
	[[nodiscard]] bool IsTileAtPosition(glm::vec2 position) const;
	[[nodiscard]] int GetTileAmount() const;
	[[nodiscard]] int GetBottomRowAmount() const;
private:
	void SpawnTiles();
	void CreateTile(glm::vec3 pos, int c, int r);
	void CheckIfCompleted() const;
	const int m_BottomRowAmount;
	float m_TileWidth{}, m_TileSmallestHeight{};
	glm::vec2 m_TileStandOffset{};
	std::vector<WorldTile_Comp*> m_pWorldTiles{ };

	std::shared_ptr<Texture2D> m_pNormalTexture
	                           , m_pHighlightTexture
							   , m_pIntermediateTexture;
};
