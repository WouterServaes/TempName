#pragma once

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

		BaseComponent(componentType type) :componentType(type) {};
		virtual ~BaseComponent() = default;

		const componentType componentType;

		//saves a ptr to the game object that owns this component
		void SetGameObject(GameObject* pGameObject)
		{
			if (m_pGameObject == nullptr)
				m_pGameObject = pGameObject;
			else
				throw(std::runtime_error(std::string("SetGameObject(GameObject*) -> Already set pointer to gameObject, can't change this")));
		};

		virtual void Update() {};
		virtual void Render() const {};
	protected:
		bool m_IsInitialized{ false };
		GameObject* m_pGameObject{ nullptr };
	};
}
