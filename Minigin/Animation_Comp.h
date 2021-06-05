#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class Texture2D;
class Render_Comp;
class Animation_Comp final : public BaseComponent
{
public:
	Animation_Comp() = delete;
	/// <summary>
	/// Used for animations made up of multiple image files
	/// </summary>
	Animation_Comp(const std::string& folder, const std::string& baseName, int amountOfImages, int animationFramesPerSecond);

	/// <summary>
	/// Used for animations on a single image sheet
	/// </summary>
	Animation_Comp(const std::string& animationSheet, int imageAmount, int framesPerSecond, glm::vec2 frameDimensions);
	~Animation_Comp() = default;

	Animation_Comp(const Animation_Comp& other) = delete;
	Animation_Comp(Animation_Comp&& other) noexcept = delete;
	Animation_Comp& operator=(const Animation_Comp& other) = delete;
	Animation_Comp& operator=(Animation_Comp&& other) noexcept = delete;

	/// <summary>
	/// Updates the animation
	/// </summary>
	void Update() override;

	/// <summary>
	/// Initializes the Render component of the game object
	/// </summary>
	void Start() override;

	[[nodiscard]] const glm::vec2& GetFrameDimensions() const { return m_FrameDimensions; }
	[[nodiscard]] int GetFramesPerSecond() const { return m_FramesPerSecond; }
	[[nodiscard]] int GetAmountOfFrames() const { return m_AmountOfFrames; }
	[[nodiscard]] const std::string& GetTextureName() const;

	/// <summary>
	/// Updates the animation sheet to a new one
	/// </summary>
	void UpdateAnimationSheet(const std::string& animationSheet, int imageAmount, int framesPerSecond, glm::vec2 frameDimensions);
private:

	///Used for animations made up of multiple image files, gets the correct fileName of an image
	[[nodiscard]] std::string GetImageName(int imgNr, const std::string& folderName, const std::string& imageBaseName) const;

	//Update functions
	void MultipleTexturesUpdate();
	void SingleTextureUpdate();

	//Textures of the frames, when a sheet is used only m_Textures[0] gets used
	std::vector<std::shared_ptr<Texture2D>> m_Textures{};

	float m_ElapsedTime{ 0.f };
	int m_CurrentFrameColumn{ 0 }, m_CurrentFrameRow{ 0 }, m_AmountOfFrames, m_FramesPerSecond;

	glm::vec2 m_FrameDimensions{};

	Render_Comp* m_pRenderComponent{ nullptr };

	bool m_MultipleImages{ false };

};
