#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Font.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#pragma warning(pop)
namespace dae
{
	class Texture2D;
	class Texture2D;
	class TextComponent :public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::string& font, int fontSize,const glm::vec4& color = {255.f, 255.f, 255.f, 1.f});
		~TextComponent() = default;
		void UpdateText(const std::string& newText);
		void Render()const override { m_pGameObject->GetComponent<RenderComponent>()->Render(); };
	private:
		
		std::shared_ptr<Font> m_pFont;
		std::string m_Text;
		glm::vec4 m_Color;
	};
}

