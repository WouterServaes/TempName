#pragma once
#include "GameObject.h"
#include "Logger.h"
namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		
		//saves a ptr to the game object that owns this component
		void SetGameObject(GameObject* pGameObject)
		{
			if (m_pGameObject == nullptr)
				m_pGameObject = pGameObject;
			else
				Logger::LogError("SetGameObject(GameObject*) -> Already set pointer to gameObject, can't change this");
		}

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
		virtual void Start() {};
	protected:
		GameObject* m_pGameObject{ nullptr };
	};
}
