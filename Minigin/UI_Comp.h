#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Transform_Comp;
	class UI_Comp: public BaseComponent
	{
	public:
		UI_Comp() = default;
		~UI_Comp() = default;
		void Update() override = 0 ;
		void Start() override;
	protected:
		const Transform_Comp* m_pTransformComponent{nullptr};
	};

	class StartUI final:public UI_Comp
	{
	public:
		StartUI() = default;
		~StartUI() = default;
		void Update() override;
	};

	class FpsUI final:public UI_Comp
	{
	public:
		FpsUI() = default;
		~FpsUI() = default;
		void Update() override;
	};
}

