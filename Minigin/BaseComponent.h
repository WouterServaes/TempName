#pragma once
#include <glm/detail/type_vec.hpp>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "GameObject.h"

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		enum class componentType
		{
			render = 0,
			text = 1,
			transform = 2,
			fps = 3,
			animation = 4
		};
		
		BaseComponent(componentType type):m_ComponentType(type){};
		virtual ~BaseComponent() = default;

		const componentType m_ComponentType;
		void SetGameObject(GameObject* pGameObject)
		{
			if (m_pGameObject == nullptr)
				m_pGameObject = pGameObject;
			else
				throw(std::runtime_error(std::string("SetGameObject(GameObject*) -> Already set pointer to gameObject, can't change this")));
		};
		
		//not pure virtual -> I loop over every component in GameObject and call these from every component
		virtual void Update() {};
#pragma warning(push)
#pragma warning(disable: 4100) //not using renderPos throws a warning
		virtual void Render(const glm::vec3& renderPos) const {};
#pragma warning(pop)
	protected:
		GameObject* m_pGameObject{nullptr};
		
	};
}
