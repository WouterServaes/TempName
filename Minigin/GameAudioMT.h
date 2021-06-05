#pragma once
#include "AudioInterface.h"
#include "PlayMessage.h"
#include <thread>
#include <condition_variable>

//https://gameprogrammingpatterns.com/event-queue.html


//Multi Threaded Game Audio 
class GameAudioMT final :public AudioInterface
{
public:
	GameAudioMT() = default;
	~GameAudioMT() = default;
	GameAudioMT(const GameAudioMT& other) = delete;
	GameAudioMT(GameAudioMT&& other) noexcept = delete;
	GameAudioMT& operator=(const GameAudioMT& other) = delete;
	GameAudioMT& operator=(GameAudioMT&& other) noexcept = delete;

	void Start() override;
	void End() override;
	void PlaySound(int soundId, int volume) override;
	void StopSound(int soundId) override;
	void Update() override;
	void HandleSoundQueue();
	void AddAudioFile(const char* fileName) override;
private:
	static const int MaxPendingSounds{ 10 };
	std::vector<PlayMessage> m_SoundQueue{};
	std::vector<std::string> m_AudioFiles{};
	std::vector<int> m_AudioIds{};

	std::thread m_AudioThread{};
	std::condition_variable m_ConditionVariable{};
	std::mutex m_Mutex{};

	std::atomic_bool m_EndAudio{ false };
};
