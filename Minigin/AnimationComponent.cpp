#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "AnimationComponent.h"
#include "RenderComponent.h"
#include "Time.h"

dae::AnimationComponent::AnimationComponent(const std::string& folder, const std::string& baseName, int amountOfImages, int animationFramesPerSecond)
	:BaseComponent(componentType::animation), m_AmountOfFrames(amountOfImages)
	, m_FramesPerSecond(animationFramesPerSecond)
{
	//save all texture frames as a Texture2D
	for (int idx{}; idx < amountOfImages; ++idx)
		m_Textures.push_back(ResourceManager::GetInstance().LoadTexture(GetImageName(idx, folder, baseName))); 
}

void dae::AnimationComponent::Update()
{
	if (!m_IsInitialized)
	{
		m_IsInitialized = true;
		m_pRenderComponent = m_pGameObject->GetComponent<RenderComponent>();
		m_pRenderComponent->UpdateTexture(m_Textures[0]);
		
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

std::string dae::AnimationComponent::GetImageName(int imgNr, const std::string& folderName, const std::string& imageBaseName) const
{
	auto imageFileName{ folderName + "/" + imageBaseName };

	if (imgNr >= 10)
	{
		if (m_AmountOfFrames >= 100 && imgNr <= 100)
			imageFileName += "0" + std::to_string(imgNr) + ".";
		else
			imageFileName += std::to_string(imgNr) + ".";
	}
	else
		imageFileName += "0" + std::to_string(imgNr) + ".";	
	imageFileName += "png";

	return imageFileName;
}
