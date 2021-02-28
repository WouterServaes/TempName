#pragma once

namespace dae
{
	
	class BaseComponent;
	class Texture2D;
	class TransformComponent;
	class Subject;
	class Scene;
	class GameObject final
	{
	public:
		GameObject(const wchar_t* pObjectName, Scene* pScene,bool isSubject = false);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;

		void AddComponent(BaseComponent* component); //Adds the desired component to this gameObject (by adding to a BaseComponent vector m_pComponents)

		[[nodiscard]] bool IsMarkedForDeletion() const { return m_MarkForDeletion; };
		void MarkForDeletion() { m_MarkForDeletion = true; };
		[[nodiscard]] bool NeedsToBeRendered()const { return m_NeedsToBeRendered; };
		[[nodiscard]] bool IsActive()const { return m_IsActive; };
		void SetActive(const bool active) { m_IsActive = active; };
		
		template<typename T>
		T* GetComponent()
		{
			for (auto& comp : m_pComponents)
			{
				if (typeid(*comp) == typeid(T))
					return static_cast<T*>(comp);
			}

			throw(std::runtime_error(std::string("GetComponent() -> Component doesn't exist on GameObject")));
		};

		template<typename T>
		const T* GetConstComponent() const
		{
			for (auto& comp : m_pComponents)
			{
				if (typeid(*comp) == typeid(T))
					return static_cast<T*>(comp);
			}

			throw(std::runtime_error(std::string("GetConstComponent() -> Component doesn't exist on GameObject")));
		}
		
		[[nodiscard]] TransformComponent* GetTransformComponent();
		[[nodiscard]] const wchar_t* GetName()const { return m_pObjectName; };

		[[nodiscard]]Subject* GetSubject()const;
		[[nodiscard]] Scene* GetCurrentScene()const;
	private:
		std::vector<BaseComponent*> m_pComponents{};

		bool m_MarkForDeletion{ false }; //true: this game object will be deleted from the scene at the end of the current update
		bool m_NeedsToBeRendered{ false }; //true: Render() of this gameObject will be called from the scene manager, not every game object needs to be rendered.
		bool m_IsActive{ true };
		const wchar_t* m_pObjectName;

		Scene * const m_pCurrentScene;
		
		Subject * const m_pSubject{ nullptr };

		
	};
}
