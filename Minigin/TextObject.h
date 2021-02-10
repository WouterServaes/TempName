#pragma once
#include "SceneObject.h"
#include "Transform.h"
#include "FpsComponent.h"
#include "TextComponents.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextObject final : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		explicit TextObject(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

		void AddFpsComponent();
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;


		std::unique_ptr<FpsComponent> m_pFpsComp{nullptr};
		std::unique_ptr<ChangeableTextComponent> m_pChangeableTextComp{ nullptr };
		std::unique_ptr<ColoredTextComponent>m_pColoredTextComp{ nullptr };
	};
}
