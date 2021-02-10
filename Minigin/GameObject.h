#pragma once
#include "Transform.h"
#include "SceneObject.h"

#include "RenderComponent.h"

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


		void AddRenderComponent(const std::string& textureFileName);
	private:
		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};

		std::unique_ptr<RenderComponent> m_RenderComp{ nullptr };
		
	};
}
