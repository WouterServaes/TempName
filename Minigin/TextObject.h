#pragma once
#include "SceneObject.h"
#include "Transform.h"
#include "TextComponents.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec4.hpp>
#pragma warning(pop)
namespace dae
{
	class Font;
	class Texture2D;
	class TextObject final : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void SetPosition(float x, float y);

		explicit TextObject(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

		void AddChangleableTextComponent();
		void AddColoredTextComponent(const glm::vec4& color);
		void AddFpsCounterComponent();
	private:
		std::string m_Text;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;


		std::unique_ptr<ChangeableTextComponent> m_pChangeableTextComp{ nullptr };
		std::unique_ptr<ColoredTextComponent>m_pColoredTextComp{ nullptr };
		std::unique_ptr<FpsCounterComponent>m_pFpsCounterComp{ nullptr };
		bool m_IsInitialized{ false };
	};
}
