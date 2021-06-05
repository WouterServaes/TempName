#pragma once
#include "GameObject.h"
#include "Logger.h"

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

	/// <summary>
	/// saves a ptr to the game object that owns this component, called when adding the component to the game object
	/// </summary>
	void SetGameObject(GameObject* pGameObject)
	{
		if (m_pGameObject == nullptr)
			m_pGameObject = pGameObject;
		else
			Logger::LogError("SetGameObject(GameObject*) -> Already set pointer to gameObject, can't change this");
	}

	/// <summary>
	/// Calls GetComponent() on the game object owning this component
	/// </summary>
	template<typename T>
	T* GetComponent()
	{
		return m_pGameObject->GetComponent<T>();
	}

	/// <summary>
	/// Calls GetConstComponent() on the game object owning this component
	/// </summary>
	template<typename T>
	const T* GetConstComponent() const
	{
		return m_pGameObject->GetConstComponent<T>();
	}

	//To-be-overloaded function of a component
	//not every component needs an Update, Render or a Start but these get called from the GameObject
	
	virtual void Update() {}
	virtual void Render() const {}
	virtual void Start() {}
protected:
	//ptr to the game object that owns this component
	GameObject* m_pGameObject{ nullptr };
};
