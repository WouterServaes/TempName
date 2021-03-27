#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Transform_Comp;
	class UIComponent: public BaseComponent
	{
	public:
		UIComponent() :BaseComponent(componentType::ui) {};
		~UIComponent() = default;
		void Update() override = 0 ;
	protected:
		const Transform_Comp* m_pTransformComponent{nullptr};
	};

	class StartUI final:public UIComponent
	{
	public:
		StartUI() = default;
		~StartUI() = default;
		void Update() override;
	};

	class FpsUI final:public UIComponent
	{
	public:
		FpsUI() = default;
		~FpsUI() = default;
		void Update() override;
	};
}

