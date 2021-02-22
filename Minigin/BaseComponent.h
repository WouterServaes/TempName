#pragma once
#include <glm/detail/type_vec.hpp>
#pragma warning(push)
#include "GameObject.h"

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		enum class componentType
		{
			render,
			text ,
			transform,
			animation,
			ui 
		};

		BaseComponent(componentType type) :m_ComponentType(type) {};
		virtual ~BaseComponent() = default;

		const componentType m_ComponentType;

		void SetGameObject(GameObject* pGameObject) //Only works when the game object ptr is a nullptr
		{
			if (m_pGameObject == nullptr)
				m_pGameObject = pGameObject;
			else
				throw(std::runtime_error(std::string("SetGameObject(GameObject*) -> Already set pointer to gameObject, can't change this")));
		};

		virtual void Update() {};
		virtual void Render() const {};
	protected:
		GameObject* m_pGameObject{ nullptr };
		bool m_IsInitialized{ false };
	};
}
