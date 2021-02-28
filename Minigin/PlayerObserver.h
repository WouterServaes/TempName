#pragma once
#include "Observer.h"

namespace dae
{
	class PlayerObserver :
	    public Observer
	{
	public:
		PlayerObserver() = default;
		~PlayerObserver() = default;
		void OnNotify(const std::shared_ptr<GameObject>& gameObject, Event event) override;

	private:
		void UpdateHealthUi(const std::shared_ptr<GameObject>& gameObject);
		void ShowPlayerDied(const std::shared_ptr<GameObject>& gameObject);
		
	};
	
}

