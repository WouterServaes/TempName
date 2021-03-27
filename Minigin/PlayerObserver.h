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
		void OnNotify(GameObject* gameObject, Event event) override;

	private:
		void UpdateHealthUi(const GameObject* gameObject);
		void ShowPlayerDied(GameObject* gameObject);
		void HandleDefeatedCoily(GameObject* gameObject);
		void HandleColorChanged(GameObject* gameObject);
		void HandleCatchedSlickOrSame(GameObject* gameObject);
		void HandleLeftDiskAtEnd(GameObject* gameObject);

		void AddScore(int amount, GameObject* playerObj);
		Text_Comp* GetScoreTextComponent(const GameObject* playerObj);
		Score_Comp* GetScoreComponent(GameObject* const playerObj);
	};
}
