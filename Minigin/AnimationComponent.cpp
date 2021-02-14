#include "MiniginPCH.h"
#include "AnimationComponent.h"
#include "ResourceManager.h"
#include "time.h"
dae::AnimationComponent::AnimationComponent(const std::string& folder, const std::string& baseName, RenderComponent::ImageTypes fileType, int amountOfImages, int sequenceFramesPerSecond)
	:BaseComponent(componentType::animation), m_AmountOfFrames(amountOfImages)
	, m_pFolderName(new std::string(folder)), m_pImageBaseName(new std::string(baseName))
	, m_FileType{fileType}, m_FramesPerSecond(sequenceFramesPerSecond)
{
	for (int idx{}; idx < amountOfImages; ++idx)
		m_Textures.push_back(ResourceManager::GetInstance().LoadTexture(GetImageName(idx))); //save all texture frames
	
	m_pRenderComp = std::make_unique<RenderComponent>(m_Textures[0]); //add first frame to render component
}

void dae::AnimationComponent::Update()
{
	m_ElapsedTime += Time::GetInstance().deltaTime;

	if (m_ElapsedTime >= m_FramesPerSecond/60)
	{
		if (m_CurrentFrame == m_AmountOfFrames-1)
			m_CurrentFrame = 0;
		else
			m_CurrentFrame += 1;

		m_ElapsedTime = 0.f;
		m_pRenderComp->UpdateTexture(m_Textures[m_CurrentFrame]);
	}
}

void dae::AnimationComponent::Render(const glm::vec3& renderPos) const
{
	m_pRenderComp->Render(renderPos);
}

std::string dae::AnimationComponent::GetImageName(int imgNr) const
{
	std::string imageFileName{};
	imageFileName = *m_pFolderName + "/" + *m_pImageBaseName;

	if (imgNr >= 10)
	{
		if(m_AmountOfFrames >=100 && imgNr <= 100)
			imageFileName += "0" + std::to_string(imgNr) + ".";
		else
			imageFileName += std::to_string(imgNr) + ".";
	}
	else
		imageFileName += "0" + std::to_string(imgNr) + ".";

	switch (m_FileType)
	{
	case RenderComponent::ImageTypes::png:
		imageFileName += "png";
		break;
	}

	return imageFileName;
}