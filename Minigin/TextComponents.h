#pragma once

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
	private:
		std::string t{};
	};

	class ColoredTextComponent final: public BaseTextComponent
	{
		
	};
}


