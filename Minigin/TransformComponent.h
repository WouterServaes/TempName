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

		explicit TransformComponent(const glm::vec3& position) :m_Position(position), BaseComponent(componentType::transform) { m_IsInitialized = true; };
		explicit TransformComponent(float x, float y, float z = 0.f) :m_Position(glm::vec3(x, y, z)), BaseComponent(componentType::transform) { m_IsInitialized = true; }
		~TransformComponent() = default;
		void SetPosition(const glm::vec3& position) { m_Position = position; };
		[[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; };
		void Translate(const glm::vec3& translation);
	private:
		glm::vec3 m_Position;
	};
}
