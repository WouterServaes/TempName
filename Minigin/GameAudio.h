#pragma once
#include "BaseAudio.h"
#include "PlayMessage.h"
//https://gameprogrammingpatterns.com/event-queue.html

namespace dae
{
	class GameAudio final:public BaseAudio
	{
	public:
		void Start() override;
		void End() override;
		void PlaySound(int soundId, int volume) override;
		void StopSound(int soundId) override;
		void Update() override;
	private:
		static const int MaxPendingSounds{10};
		PlayMessage m_SoundQueue[MaxPendingSounds]{};
		std::atomic<int> m_NumPending{ 0 };
		bool m_QuitAudio{ false };
		bool m_NeedsToPlayAudio{ false };
	};
}

