#pragma once
#include "BaseAudio.h"
#include "PlayMessage.h"
//https://gameprogrammingpatterns.com/event-queue.html

namespace dae
{
	class GameAudio final:public BaseAudio
	{
	public:
		void PlaySound(int soundId, int volume) override;
		void StopSound(int soundId) override;
		void Update() override;
		void Start() override;
		void End() override;
	private:
		static const int MaxPendingSounds{10};
		PlayMessage m_SoundQueue[MaxPendingSounds]{};
		int m_NumPending{0};
	};
}

