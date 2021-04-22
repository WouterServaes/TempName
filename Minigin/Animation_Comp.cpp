#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Animation_Comp.h"
#include "Render_Comp.h"
#include "Time.h"

dae::Animation_Comp::Animation_Comp(const std::string& folder, const std::string& baseName, int amountOfImages, int animationFramesPerSecond)
	:m_AmountOfFrames(amountOfImages)
	, m_FramesPerSecond(animationFramesPerSecond)
{
	m_MultipleImages = true;
	//save all texture frames as a Texture2D
	for (int idx{}; idx < amountOfImages; ++idx)
		m_Textures.push_back(ResourceManager::GetInstance().LoadTexture(GetImageName(idx, folder, baseName))); 
}

dae::Animation_Comp::Animation_Comp(const std::string& animationSheet, int , int ,
	glm::vec2 )
{
	m_Textures[0] = ResourceManager::GetInstance().LoadTexture(animationSheet);
}

void dae::Animation_Comp::Start()
{
	m_pRenderComponent = m_pGameObject->GetComponent<Render_Comp>();

	m_pRenderComponent->UpdateTexture(m_Textures[0]);

}

void dae::Animation_Comp::Update()
{
	m_ElapsedTime += Time::GetInstance().deltaTime;

	if (m_ElapsedTime >= 1.f/float(m_FramesPerSecond))
	{
		if (m_CurrentFrame == m_AmountOfFrames - 1)
			m_CurrentFrame = 0;
		else
			m_CurrentFrame += 1;

		m_ElapsedTime = 0.f;
		if (m_MultipleImages)
			MultipleTexturesUpdate();
		else
			SingleTextureUpdate();
		
	}
}

void dae::Animation_Comp::MultipleTexturesUpdate()
{
	m_pRenderComponent->UpdateTexture(m_Textures[m_CurrentFrame]);
}

void dae::Animation_Comp::SingleTextureUpdate()
{
	
}

std::string dae::Animation_Comp::GetImageName(int imgNr, const std::string& folderName, const std::string& imageBaseName) const
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


