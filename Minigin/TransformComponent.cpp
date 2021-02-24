#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "Transform.h"

dae::TransformComponent::~TransformComponent()
{
	delete m_Transform;
}

dae::TransformComponent::TransformComponent(const glm::vec3& position)
: BaseComponent(componentType::transform)
{
	m_Transform = new Transform();
	m_Transform->SetPosition(position.x, position.y, position.z);
	m_IsInitialized = true;
};

dae::TransformComponent::TransformComponent(const float x, const  float y, const  float z)
:BaseComponent(componentType::transform)
{
	m_Transform = new Transform();
	m_Transform->SetPosition(x, y, z);
	m_IsInitialized = true;
}