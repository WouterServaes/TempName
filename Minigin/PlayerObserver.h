#pragma once
#include "Observer.h"

namespace dae
{
	class Text_Comp;
	class Score_Comp;
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
		void HandleDefeatedCoily(const std::shared_ptr<GameObject>& gameObject);
		void HandleColorChanged (const std::shared_ptr<GameObject>& gameObject);
		void HandleCatchedSlickOrSame (const std::shared_ptr<GameObject>& gameObject);
		void HandleLeftDiskAtEnd(const std::shared_ptr<GameObject>& gameObject);

		void AddScore(int amount, const std::shared_ptr<GameObject>& playerObj);
		Text_Comp* GetScoreTextComponent(const std::shared_ptr<GameObject>& playerObj);
		Score_Comp* GetScoreComponent(const std::shared_ptr<GameObject>& playerObj);
	};
	
}

