#pragma once
#include "BaseComponent.h"
#include "Render_Comp.h"
#include "GameObject.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec4.hpp>
#pragma warning(pop)

#include "Font.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>

class Text_Comp final :public BaseComponent
{
public:
	Text_Comp() = delete;
	Text_Comp(const std::string& text, const std::string& font, int fontSize, const glm::vec4& color = { 255.f, 255.f, 255.f, 1.f });
	~Text_Comp();
	Text_Comp(const Text_Comp& other) = delete;
	Text_Comp(Text_Comp&& other) noexcept = delete;
	Text_Comp& operator=(const Text_Comp& other) = delete;
	Text_Comp& operator=(Text_Comp&& other) noexcept = delete;

	void UpdateText(const std::string& newText);
	void Start() override;

private:
	void InitializeText() const;
	std::shared_ptr<Font> m_pFont{};
	std::string m_Text{};

	Render_Comp* m_pRenderComponent{ nullptr };
	SDL_Color* m_Color{ nullptr };
};
