#include "MiniginPCH.h"
#include "Transform.h"

dae::Transform& dae::Transform::operator=(const Transform& other)
{
	m_Position = other.GetPosition();
	return *this;
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::Transform::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}

void dae::Transform::Translate(const glm::vec3& translation)
{
	m_Position *= translation;
}

void dae::Transform::Translate(const float x,const float y,const float z)
{
	m_Position.x *= x;
	m_Position.y *= y;
	m_Position.z *= z;
}