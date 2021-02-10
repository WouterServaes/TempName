#include "MiniginPCH.h"
#include "TextComponents.h"

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