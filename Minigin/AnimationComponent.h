#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class RenderComponent;
	class AnimationComponent final :
		public BaseComponent
	{
	public:
		AnimationComponent(const std::string& folder, const std::string& baseName, int amountOfImages, int animationFramesPerSecond);
		~AnimationComponent() = default;
		void Update() override;
	private:
		[[nodiscard]] std::string GetImageName(int imgNr, const std::string& folderName, const std::string& imageBaseName) const;
		
		std::vector<std::shared_ptr<Texture2D>> m_Textures{};
		
		float m_ElapsedTime{ 0.f }, m_AnimationSpeed;
		int m_CurrentFrame{ 0 }, m_AmountOfFrames, m_FramesPerSecond;

		RenderComponent* m_pRenderComponent{ nullptr };
	};
}
