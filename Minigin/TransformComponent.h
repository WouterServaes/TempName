#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Transform;
	class TransformComponent final :public BaseComponent
	{
	public:
		explicit TransformComponent(const glm::vec3& position);
		explicit TransformComponent(float x, float y, float z = 0.f);
		~TransformComponent();

		[[nodiscard]] Transform* GetTransform() const { return m_Transform; };
	private:
		Transform* m_Transform{ nullptr };
	};
}
