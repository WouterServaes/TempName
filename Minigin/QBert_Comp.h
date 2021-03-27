#pragma once
#include "BaseComponent.h"
namespace dae
{
	class Health_Comp;
	class QBert_Comp final : public BaseComponent
	{
	public:
		QBert_Comp() = default;
		~QBert_Comp() = default;

		void Update() override;

	private:
		Health_Comp* m_pHealthComp;
		bool m_IsInitialized{ false };
	};

}
