#include "MiniginPCH.h"
#include "Score_Comp.h"

#include "Scene.h"
#include "Text_Comp.h"

void Score_Comp::Update()
{
	if (!m_UpdatedStartUi)
	{
		UpdateUi();
		m_UpdatedStartUi = true;
	}
}

void Score_Comp::AttachTextComp(Text_Comp* pTextComp)
{
	m_pScoreText = pTextComp;
}

void Score_Comp::UpdateUi() const
{
	if (!m_pScoreText)
	{
		Logger::LogInfo("Score_Comp on " + m_pGameObject->GetName() + " no text comp assigned!");
		return;
	}
	const auto text{ "Score: " + std::to_string(m_CurrentScore) };
	m_pScoreText->UpdateText(text);
}