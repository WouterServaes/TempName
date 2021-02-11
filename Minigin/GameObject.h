#pragma once
#include "Transform.h"
#include "SceneObject.h"

#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		void AddComponent(std::unique_ptr<BaseComponent> component);
	private:
		Transform m_Transform;

		std::vector<std::unique_ptr<BaseComponent>> m_pComponents{ };
	};
}
