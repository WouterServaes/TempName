#pragma once
#include "Singleton.h"

class Texture2D;
class Font;
class ResourceManager final : public Singleton<ResourceManager>
{
public:
	~ResourceManager() = default;
	ResourceManager(const ResourceManager& other) = delete;
	ResourceManager(ResourceManager&& other) noexcept = delete;
	ResourceManager& operator=(const ResourceManager& other) = delete;
	ResourceManager& operator=(ResourceManager&& other) noexcept = delete;

	/// <summary>
	/// Loads libraries using SDL macros and sets the dataPath
	/// </summary>
	/// <param name="dataPath">relative path to data folder</param>
	void Init(const std::string& dataPath);

	///Makes a Texture2 shared ptr and returns it
	[[nodiscard]] std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;

	///Makes a Font shared ptr and returns it
	[[nodiscard]] std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;
	std::string m_DataPath{};
};
