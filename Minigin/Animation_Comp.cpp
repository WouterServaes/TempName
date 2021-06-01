#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Animation_Comp.h"
#include "Render_Comp.h"
#include "Time.h"

Animation_Comp::Animation_Comp(const std::string& folder, const std::string& baseName, const int amountOfImages, const int animationFramesPerSecond)
	:m_AmountOfFrames(amountOfImages)
	, m_FramesPerSecond(animationFramesPerSecond)
{
	m_MultipleImages = true;
	//save all texture frames as a Texture2D
	for (int idx{}; idx < amountOfImages; ++idx)
		m_Textures.push_back(ResourceManager::GetInstance().LoadTexture(GetImageName(idx, folder, baseName)));
}

Animation_Comp::Animation_Comp(const std::string& animationSheet, const int imageAmount, const int framesPerSecond,
	const glm::vec2 frameDimensions)
{
	m_FrameDimensions = frameDimensions;
	m_AmountOfFrames = imageAmount;
	m_FramesPerSecond = framesPerSecond;

	m_Textures.push_back(ResourceManager::GetInstance().LoadTexture(animationSheet));
}

void Animation_Comp::Start()
{
	m_pRenderComponent = m_pGameObject->GetComponent<Render_Comp>();

	if(m_pRenderComponent)
		m_pRenderComponent->UpdateTexture(m_Textures[0]);
}

void Animation_Comp::Update()
{
	m_ElapsedTime += Time::GetInstance().deltaTime;

	if (m_ElapsedTime >= 1.f / float(m_FramesPerSecond))
	{
		m_ElapsedTime = 0.f;

		if (m_MultipleImages)
			MultipleTexturesUpdate();
		else
			SingleTextureUpdate();
	}
}

void Animation_Comp::MultipleTexturesUpdate()
{
	if (m_CurrentFrameColumn == m_AmountOfFrames - 1)
		m_CurrentFrameColumn = 0;
	else
		m_CurrentFrameColumn += 1;

	if (m_pRenderComponent)
	{
		m_pRenderComponent->UpdateTexture(m_Textures[m_CurrentFrameColumn]);
	}
}

void Animation_Comp::SingleTextureUpdate()
{
	const auto texDim{ m_Textures[0]->GetTextureData().Dimensions };
	if (m_CurrentFrameColumn + 1 >= texDim.x / m_FrameDimensions.x)
	{
		m_CurrentFrameColumn = 0;

		const auto rows{ texDim.y / m_FrameDimensions.y };
		if (rows == 1 || m_CurrentFrameRow + 1 >= texDim.y / m_FrameDimensions.y)
			m_CurrentFrameRow = 0;
		else
			m_CurrentFrameRow++;
	}
	else
		m_CurrentFrameColumn++;

	const float srcX{ m_FrameDimensions.x * m_CurrentFrameColumn }
	, srcY{ m_FrameDimensions.y * m_CurrentFrameRow };
	if (m_pRenderComponent)
		m_pRenderComponent->UpdateTexture(m_Textures[0], m_FrameDimensions.x, m_FrameDimensions.y, srcX, srcY, m_FrameDimensions.x, m_FrameDimensions.y);
}

std::string Animation_Comp::GetImageName(const int imgNr, const std::string& folderName, const std::string& imageBaseName) const
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