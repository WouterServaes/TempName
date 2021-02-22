#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "RenderComponent.h"

namespace dae
{
	class Texture2D;
	class AnimationComponent final :
		public BaseComponent
	{
	public:
		AnimationComponent(const std::string& folder, const std::string& baseName, RenderComponent::ImageTypes fileType, int amountOfImages, int animationFramesPerSecond);
		AnimationComponent(const std::string fileName, int amountOfFrames, float animationSpeed );
		~AnimationComponent() = default;
		void Update() override;
	private:
		[[nodiscard]] std::string GetImageName(int imgNr) const;
		std::vector<std::shared_ptr<Texture2D>  >m_Textures{};
		std::shared_ptr<Texture2D> m_pTexture{};
		float m_ElapsedTime{ 0.f }, m_AnimationSpeed;
		int m_CurrentFrame{ 0 }, m_AmountOfFrames, m_FramesPerSecond;

		const std::string* m_pFolderName, * m_pImageBaseName;
		const std::string m_FileName;
		RenderComponent::ImageTypes m_FileType;
		RenderComponent* m_pRenderComponent{ nullptr };
	};
}
