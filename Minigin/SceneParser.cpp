#include "MiniginPCH.h"
#include "SceneParser.h"

#include <fstream>

#include "rapidjson.h"
#include "document.h"
#include "istreamwrapper.h"
std::vector<std::shared_ptr<SceneParser::SceneData>> SceneParser::m_pSceneDatas{};

void SceneParser::LoadGameFromFile(const std::string& filePath)
{
	rapidjson::Document jsonDoc;
	ReadJson(jsonDoc, filePath);
	SaveJsonData(jsonDoc);
}

std::shared_ptr<SceneParser::SceneData> SceneParser::GetSceneData(const int sceneNr)
{
	if (sceneNr >= static_cast<int>(m_pSceneDatas.size()))
		Logger::LogError("SceneParser:: GetSceneData() given sceneNr exceeds saved scenes! (sceneNr: " + std::to_string(sceneNr) + ")");
	return m_pSceneDatas.at(sceneNr);
}

SceneParser::CreatureData SceneParser::GetCreatureData(const std::string& creatureName,const int sceneNr)
{
	const auto creatures{ m_pSceneDatas.at(sceneNr)->Creatures };
	const auto creature{
		std::find_if(creatures.begin(), creatures.end(), [creatureName](const CreatureData& cr)
			{
				return cr.Name == creatureName;
			})
	};
	
	if (creature == creatures.end())
		Logger::LogError("SceneParser::GetCreatureData: no creature with name " + creatureName + " found in scene nr " + std::to_string(sceneNr) + "!");

	return *creature;
}

void SceneParser::ReadJson(rapidjson::Document& jsonDoc, const std::string& filePath)
{
	std::ifstream is{ filePath };
	rapidjson::IStreamWrapper isw(is);

	const bool failedParse{ jsonDoc.ParseStream(isw).HasParseError() };

	if (failedParse)
		Logger::LogError("Error when trying to parse the file!");
}

void SceneParser::SaveJsonData(const rapidjson::Document& jsonDoc)
{
	using namespace rapidjson;
	m_pSceneDatas.clear();
	for (rapidjson::Value::ConstValueIterator valueIt{ jsonDoc.Begin() }; valueIt != jsonDoc.End(); ++valueIt)
	{
		auto pSceneData{ std::make_shared<SceneData>() };
		const rapidjson::Value& scene{ *valueIt };
		pSceneData->Name = scene["name"].GetString();
		pSceneData->PyramidSize = scene["pyramidSize"].GetInt();
		pSceneData->NormalTileTexture = scene["normalTileTex"].GetString();
		pSceneData->IntermediateTileTexture = scene["intermTileTex"].GetString();
		pSceneData->HighlightedTileTexture = scene["highlightTileTex"].GetString();
		pSceneData->Font = scene["font"].GetString();

		pSceneData->FontColor.r = scene["fontColor"][0].GetFloat();
		pSceneData->FontColor.g = scene["fontColor"][1].GetFloat();
		pSceneData->FontColor.b = scene["fontColor"][2].GetFloat();
		pSceneData->FontColor.a = scene["fontColor"][3].GetFloat();

		const Value& players{ scene["players"] };
		for (Value::ConstValueIterator playerIt{ players.Begin() }; playerIt != players.End(); ++playerIt)
		{
			const Value& player{ *playerIt };
			PlayerData playerData;
			playerData.StartLives = player["startLives"].GetInt();
			playerData.TextureData.imgPath = player["img"].GetString();
			playerData.TextureData.Count = player["count"].GetInt();
			playerData.TextureData.Fps = player["fps"].GetInt();
			playerData.TextureData.FrameSize.x = player["sizeX"].GetFloat();
			playerData.TextureData.FrameSize.y = player["sizeY"].GetFloat();
			pSceneData->Players.push_back(playerData);
		}

		const Value& creatures{ scene["creatures"] };
		for (Value::ConstValueIterator creatureIt{ creatures.Begin() }; creatureIt != creatures.End(); ++creatureIt)
		{
			const Value& creature{ *creatureIt };
			CreatureData creatureData;
			creatureData.Name = creature["name"].GetString();
			creatureData.TextureData.imgPath = creature["img"].GetString();
			creatureData.TextureData.Count = creature["count"].GetInt();
			creatureData.TextureData.Fps = creature["fps"].GetInt();
			creatureData.TextureData.FrameSize.x = creature["sizeX"].GetFloat();
			creatureData.TextureData.FrameSize.y = creature["sizeY"].GetFloat();
			creatureData.TimeBetweenJumps = creature["timeBetweenJumps"].GetFloat();
			pSceneData->Creatures.push_back(creatureData);
		}

		const Value& disks{ scene["disks"] };
		for (Value::ConstValueIterator diskIt{ disks.Begin() }; diskIt != disks.End(); ++diskIt)
		{
			const Value& disk{ *diskIt };
			DiskData diskData;
			std::string leftOrRight{ disk["side"].GetString() };
			diskData.Side = (leftOrRight == "r") ? Transform::Side::Right : Transform::Side::Left;
			diskData.Row = disk["row"].GetInt();
			pSceneData->Disks.push_back(diskData);
		}

		m_pSceneDatas.emplace_back(pSceneData);
	}
}