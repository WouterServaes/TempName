#pragma once
#include "GameObject.h"

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
	

		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		//saves a ptr to the game object that owns this component
		void SetGameObject(GameObject* pGameObject)
		{
			if (m_pGameObject == nullptr)
				m_pGameObject = pGameObject;
			else
				throw(std::runtime_error(std::string("SetGameObject(GameObject*) -> Already set pointer to gameObject, can't change this")));
		};

		template<typename T>
		T* GetComponent()
		{
			return m_pGameObject->GetComponent<T>();
		}

		template<typename T>
		const T* GetConstComponent() const
		{
			return m_pGameObject->GetConstComponent<T>();
		}
		
		virtual void Update() {};
		virtual void Render() const {};
	protected:
		bool m_IsInitialized{ false };
		GameObject* m_pGameObject{ nullptr };
	};
}
