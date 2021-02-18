#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "Font.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec4.hpp>
#pragma warning(pop)

#include <SDL.h>
namespace dae
{
	class Texture2D;
	class Texture2D;
	class TextComponent :public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::string& font, int fontSize, const glm::vec4& color = { 255.f, 255.f, 255.f, 1.f });
		~TextComponent();
		void UpdateText(const std::string& newText);
		void Render()const override { m_pGameObject->GetComponent<RenderComponent>()->Render(); };
		void Update() override;
	private:
		void InitializeText() const;
		std::shared_ptr<Font> m_pFont;
		std::string m_Text;

		RenderComponent* m_pRenderComponent{ nullptr };
		SDL_Color* m_Color{ nullptr };
	};
}
