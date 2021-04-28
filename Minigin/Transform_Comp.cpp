#include "MiniginPCH.h"
#include "Transform_Comp.h"
#include "Transform.h"

Transform_Comp::~Transform_Comp()
{
	delete m_Transform;
}

Transform_Comp::Transform_Comp(const glm::vec3& position)

{
	m_Transform = new Transform();
	m_Transform->SetPosition(position.x, position.y, position.z);
};

Transform_Comp::Transform_Comp(const float x, const float y, const float z)
{
	m_Transform = new Transform();
	m_Transform->SetPosition(x, y, z);
}