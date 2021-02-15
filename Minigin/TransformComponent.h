#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
namespace dae
{
	class TransformComponent :public BaseComponent
	{
	public:
		TransformComponent(const glm::vec3& position) :m_Position(position), BaseComponent(componentType::transform) {};

		TransformComponent(float x, float y, float z = 0.f) :m_Position(glm::vec3(x, y, z)), BaseComponent(componentType::transform) {}
		~TransformComponent() = default;
		void SetPosition(const glm::vec3& position) { m_Position = position; };
		const glm::vec3& GetPosition() const { return m_Position; };
	private:
		glm::vec3 m_Position;
	};
}
