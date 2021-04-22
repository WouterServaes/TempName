#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
namespace dae
{
	class Texture2D;
	class Render_Comp;
	class Animation_Comp final :
		public BaseComponent
	{
	public:
		Animation_Comp(const std::string& folder, const std::string& baseName, int amountOfImages, int animationFramesPerSecond);
		Animation_Comp(const std::string& animationSheet, int imageAmount, int framesPerSecond, glm::vec2 frameDimensions);
		~Animation_Comp() = default;
		void Update() override;
		void Start() override;
	private:
		[[nodiscard]] std::string GetImageName(int imgNr, const std::string& folderName, const std::string& imageBaseName) const;

		void MultipleTexturesUpdate();
		void SingleTextureUpdate();
		
		std::vector<std::shared_ptr<Texture2D>> m_Textures{};

		std::shared_ptr<Texture2D> m_Texture{};
		float m_ElapsedTime{ 0.f }, m_AnimationSpeed;
		int m_CurrentFrame{ 0 }, m_AmountOfFrames, m_FramesPerSecond;

		Render_Comp* m_pRenderComponent{ nullptr };

		bool m_MultipleImages{ false };
	};
}
