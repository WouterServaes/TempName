#pragma once
#include "BaseComponent.h"
#include "Time.h"
#include "TextComponent.h"
namespace dae
{
	class FpsComponent final :public BaseComponent
	{
	public:
		FpsComponent(bool useTextCompToPrint = false) :BaseComponent(componentType::fps), m_UseTextCompToPrint(useTextCompToPrint){};
		~FpsComponent() = default;
		[[nodiscard]] static int GetFps() { return Time::GetInstance().fps; };
		[[nodiscard]] bool UseTextCompToPrint()const { return m_UseTextCompToPrint; };
		void Update() override;
	private:
		TextComponent* m_pTextComponent{nullptr};
		bool m_UseTextCompToPrint;
		int m_PreviousFps{};
	};
}
