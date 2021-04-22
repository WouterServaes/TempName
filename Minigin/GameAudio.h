#pragma once
#include "BaseAudio.h"
#include "PlayMessage.h"
#include <thread>
#include <condition_variable>
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
		void HandleSoundQueue();
	private:
		static const int MaxPendingSounds{10};
		std::vector<PlayMessage> m_SoundQueue{};

		std::thread m_AudioThread{};
		std::condition_variable m_ConditionVariable{};
		std::mutex m_Mutex{};

		
		std::atomic_bool m_EndAudio{ false };
	};
}

