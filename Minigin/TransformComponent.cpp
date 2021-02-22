#include "MiniginPCH.h"
#include "TransformComponent.h"

void dae::TransformComponent::Translate(const glm::vec3& translation)
{
	m_Position *= translation;
}