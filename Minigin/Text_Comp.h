#pragma once
#include "BaseComponent.h"
#include "Render_Comp.h"
#include "GameObject.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec4.hpp>
#pragma warning(pop)

#include "Font.h"
#include <SDL.h>

namespace dae
{
	class Text_Comp :public BaseComponent
	{
	public:
		Text_Comp(const std::string& text, const std::string& font, int fontSize, const glm::vec4& color = { 255.f, 255.f, 255.f, 1.f });
		~Text_Comp();
		void UpdateText(const std::string& newText);
		void Render()const override { m_pGameObject->GetComponent<Render_Comp>()->Render(); };
		void Start() override;
	private:
		void InitializeText() const;
		std::shared_ptr<Font> m_pFont;
		std::string m_Text;

		Render_Comp* m_pRenderComponent{ nullptr };
		SDL_Color* m_Color{ nullptr };
	};
}
