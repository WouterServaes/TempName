#include "MiniginPCH.h"
#include "TextComponents.h"
#include "FpsCounter.h"

void dae::ChangeableTextComponent::SetText(const std::string& text)
{
	m_NewText = text;
	m_NeedsUpdate = true;
}

void dae::ColoredTextComponent::SetTextColor(const glm::vec4& color)
{
	m_TextColor = color;
	m_NeedsUpdate = true;
}

void dae::FpsCounterComponent::UpdateFpsCounter()
{
	SetText(std::to_string(FpsCounter::GetInstance().fps) + " FPS");
}