#pragma once
#include "BaseComponent.h"
#include "Time.h"
namespace dae
{
	class FpsComponent final:public BaseComponent
	{
	public:
		FpsComponent(bool useTextCompToPrint = false):m_UseTextCompToPrint(useTextCompToPrint), BaseComponent(componentType::fps){};
		~FpsComponent() = default;
		int GetFps() const { return Time::GetInstance().fps; };
		bool UseTextCompToPrint()const { return m_UseTextCompToPrint; };
	void Update() override;
	private:
		bool m_UseTextCompToPrint;
	};
}

