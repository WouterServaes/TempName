#pragma once
#include <document.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "Transform.h"
class SceneParser
{
public:
	SceneParser() = delete;
	~SceneParser() = default;
	SceneParser(const SceneParser& other) = delete;
	SceneParser(SceneParser&& other) noexcept = delete;
	SceneParser& operator=(const SceneParser& other) = delete;
	SceneParser& operator=(SceneParser&& other) noexcept = delete;

	static void LoadGameFromFile(const std::string& filePath);
	
	struct DiskData
	{
		Transform::Side Side;
		int Row;
	};

	struct AnimTextureData
	{
		std::string imgPath{};
		int Count{};
		int Fps{};
		glm::vec2 FrameSize{};
	};

	struct CreatureData
	{
		AnimTextureData TextureData{};
		float TimeBetweenJumps{};
		std::string Name{};
	};

	struct PlayerData
	{
		AnimTextureData TextureData{};
		int StartLives{};
	};
	struct SceneData
	{
		std::string Name{};
		int PyramidSize{};
		std::string NormalTileTexture{};
		std::string IntermediateTileTexture{};
		std::string HighlightedTileTexture{};
		std::string Font{};
		glm::vec4 FontColor{};
		std::vector< PlayerData> Players{};
		std::vector<CreatureData> Creatures{};
		std::vector<DiskData> Disks{};
	};

	static std::shared_ptr<SceneData> GetSceneData(int sceneNr);
	static CreatureData GetCreatureData(const std::string& creatureName, int sceneNr);
private:
	static void ReadJson(rapidjson::Document& jsonDoc, const std::string& filePath);
	static void SaveJsonData(const rapidjson::Document& jsonDoc);
	static std::vector<std::shared_ptr<SceneData>> m_pSceneDatas;

	
};
