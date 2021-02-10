#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class BaseTextComponent
	{
	public:
		BaseTextComponent() = default;
		~BaseTextComponent() = default;
		bool GetNeedsUpdate()const { return m_NeedsUpdate; };
	protected:
		bool m_NeedsUpdate{ false };
	};
	
	class ChangeableTextComponent final:public BaseTextComponent
	{
	public:
		ChangeableTextComponent() = default;
		~ChangeableTextComponent() = default;
		void SetText(const std::string& text);
		const std::string& GetNewText() const { return m_NewText; };
	private:
		std::string m_NewText{};
	};

	class ColoredTextComponent final: public BaseTextComponent
	{
	public:
		ColoredTextComponent(const glm::vec3& color):m_TextColor(color){};
		~ColoredTextComponent() = default;
		void SetTextColor(const glm::vec3& color);
		const glm::vec3& GetTextColor()const { return m_TextColor; };
	private:
		glm::vec3 m_TextColor;
	};
}


