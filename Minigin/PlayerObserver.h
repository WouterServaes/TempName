#pragma once
#include "Observer.h"

namespace dae
{
	class TextComponent;
	class ScoreComponent;
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
		TextComponent* GetScoreTextComponent(const std::shared_ptr<GameObject>& playerObj);
		ScoreComponent* GetScoreComponent(const std::shared_ptr<GameObject>& playerObj);
	};
	
}

