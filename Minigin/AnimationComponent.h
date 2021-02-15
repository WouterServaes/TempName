#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "RenderComponent.h"

namespace dae
{
	class Texture2D;
	class RenderComponent;
	class AnimationComponent final:
	    public BaseComponent
	{
	public:
		AnimationComponent(const std::string& folder, const std::string& baseName, RenderComponent::ImageTypes fileType, int amountOfImages, int sequenceFramesPerSecond);
		~AnimationComponent()
		{
			delete m_pFolderName;
			delete m_pImageBaseName;
		};
		void Update() override;
		void Render(const glm::vec3& renderPos) const override;
	private:
		std::string GetImageName(int imgNr) const;
		std::unique_ptr<RenderComponent> m_pRenderComp{ nullptr };
		std::vector<std::shared_ptr<Texture2D>  >m_Textures{};
		float m_ElapsedTime{ 0.f };
		int m_CurrentFrame{ 0 },
		m_AmountOfFrames, //amount of frames in image sequence
		m_FramesPerSecond; //amount of frames per second from sequence
		
		const std::string* m_pFolderName, * m_pImageBaseName;
		RenderComponent::ImageTypes m_FileType;
	};
}


