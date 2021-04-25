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
		
		QBert_Comp(const QBert_Comp& other) = delete;
		QBert_Comp(QBert_Comp&& other) noexcept = delete;
		QBert_Comp& operator=(const QBert_Comp& other) = delete;
		QBert_Comp& operator=(QBert_Comp&& other) noexcept = delete;

		void Start() override;
		void Update() override;

	private:
		Health_Comp* m_pHealthComp{};
	};

}
