#pragma once
//#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		//renders the components that need to be rendered (RenderComponent & TetComponent)
		//Only gets called when this gameObject has one of these components (when it needs to be rendered)
		void Render() const override;
		
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(std::unique_ptr<BaseComponent> component); //Adds the desired component to this gameObject (by adding to a BaseComponent vector m_pComponents)
	private:
		std::vector<std::unique_ptr<BaseComponent>> m_pComponents{ };
		
		glm::vec3 GetPosition() const; //returns either position of TransformComponent if this component exists OR position 0.f, 0.f, 0.f
		int GetFps() const; //Returns fps from FpsComponent, throws error when called without FpsComponent
		void SetFirstTextCompToFps(); //updates text of first TextComponent to display text, throws error when called without TextComponent
		bool m_UseTextCompToPrintFps{false}; //Use the first text component to display fps
	};
}
