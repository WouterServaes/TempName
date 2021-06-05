#include "MiniginPCH.h"
#include "Transform.h"

Transform& Transform::operator=(const Transform& other)
{
	m_Position = other.GetPosition();
	m_Scale = other.GetScale();
	return *this;
}

void Transform::SetPosition(const float x, const float y, const float z)
{
	m_LastPosition = m_Position;
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void Transform::SetPosition(const glm::vec3& pos)
{
	m_LastPosition = m_Position;
	m_Position = pos;
}

void Transform::Translate(const glm::vec3& translation)
{
	m_LastPosition = m_Position;
	m_Position *= translation;
}

void Transform::Translate(const float x, const float y, const float z)
{
	m_LastPosition = m_Position;
	m_Position.x *= x;
	m_Position.y *= y;
	m_Position.z *= z;
}

void Transform::ScaleUniform(const float scale)
{
	Scale(glm::vec2(scale, scale));
}

void Transform::Scale(const float scaleX,const float scaleY)
{
	Scale(glm::vec2(scaleX, scaleY));
}

void Transform::Scale(const glm::vec2& scale)
{
	m_Scale = scale;
}
