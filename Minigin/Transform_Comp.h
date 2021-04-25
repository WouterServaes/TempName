#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Transform;
	class Transform_Comp final :public BaseComponent
	{
	public:

		explicit Transform_Comp(const glm::vec3& position = glm::vec3(0.f,0.f,0.f));
		explicit Transform_Comp(float x, float y, float z = 0.f);
		~Transform_Comp();
		
		Transform_Comp(const Transform_Comp& other) = delete;
		Transform_Comp(Transform_Comp&& other) noexcept = delete;
		Transform_Comp& operator=(const Transform_Comp& other) = delete;
		Transform_Comp& operator=(Transform_Comp&& other) noexcept = delete;

		[[nodiscard]] Transform* GetTransform() const { return m_Transform; };
	private:
		Transform* m_Transform{ nullptr };
	};
}
