#include "MiniginPCH.h"
#include "AnimationComponent.h"
#include "ResourceManager.h"
#include "Time.h"

dae::AnimationComponent::AnimationComponent(const std::string& folder, const std::string& baseName, RenderComponent::ImageTypes fileType, int amountOfImages, int animationFramesPerSecond)
	:BaseComponent(componentType::animation), m_AmountOfFrames(amountOfImages)
	, m_pFolderName(new std::string(folder)), m_pImageBaseName(new std::string(baseName))
	, m_FileType{ fileType }, m_FramesPerSecond(animationFramesPerSecond)
{
	for (int idx{}; idx < amountOfImages; ++idx)
		m_Textures.push_back(ResourceManager::GetInstance().LoadTexture(GetImageName(idx))); //save all texture frames
	delete m_pFolderName;
	delete m_pImageBaseName;
}

void dae::AnimationComponent::Update()
{
	if (!m_IsInitialized)
	{
		m_IsInitialized = true;
		m_pRenderComponent = m_pGameObject->GetComponent<RenderComponent>();
		m_pRenderComponent->UpdateTexture(m_Textures[0]);//set first frame to render component
		
	}

	m_ElapsedTime += Time::GetInstance().deltaTime;

	if (m_ElapsedTime >= 1.f/float(m_FramesPerSecond))
	{
		if (m_CurrentFrame == m_AmountOfFrames - 1)
			m_CurrentFrame = 0;
		else
			m_CurrentFrame += 1;

		m_ElapsedTime = 0.f;
		m_pRenderComponent->UpdateTexture(m_Textures[m_CurrentFrame]);
	}
}

std::string dae::AnimationComponent::GetImageName(int imgNr) const
{
	std::string imageFileName{};
	imageFileName = *m_pFolderName + "/" + *m_pImageBaseName;

	if (imgNr >= 10)
	{
		if (m_AmountOfFrames >= 100 && imgNr <= 100)
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

dae::AnimationComponent::AnimationComponent(const std::string fileName, int amountOfFrames, float animationSpeed)
	:BaseComponent(componentType::animation), m_AmountOfFrames(amountOfFrames), m_AnimationSpeed(animationSpeed)
, m_FileName(fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(m_FileName);
}

//make Image class
//width, height, file name, get image.