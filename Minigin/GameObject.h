#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class BaseComponent;
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;
		
		void AddComponent(BaseComponent* component); //Adds the desired component to this gameObject (by adding to a BaseComponent vector m_pComponents)

		bool IsMarkedForDeletion() const { return m_MarkForDeletion; };
		bool NeedsToBeRendered()const { return m_NeedsToBeRendered; };

		
		template<typename T>
		T* GetComponent() {
			for (auto& comp : m_pComponents)
			{
				if (typeid(*comp) == typeid(T))
					return static_cast<T*>(comp);
			}

			throw(std::runtime_error(std::string("GetComponent(type) -> Component doesn't exist on GameObject")));
		};
	
	private:
		std::vector<BaseComponent*> m_pComponents{ };

		bool m_MarkForDeletion{ false }; //true: this game object will be deleted from the scene at the end of the current update
		bool m_NeedsToBeRendered{ false }; //true: Render() of this gameObject will be called from the scene manager, not every game object needs to be rendered.
	};
}


//store GetComponent result when it's used every frame
//using raw ptrs: think about when to delete things
//smart points -> don't think about it
