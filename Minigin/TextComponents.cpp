#include "MiniginPCH.h"
#include "TextComponents.h"

void dae::ChangeableTextComponent::SetText(const std::string& text)
{
	t = text;
	m_NeedsUpdate = true;
}
