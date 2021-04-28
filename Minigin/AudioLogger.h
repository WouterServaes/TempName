#pragma once
#include "AudioInterface.h"

class AudioLogger final :public AudioInterface
{
public:

	AudioLogger(AudioInterface* audioToLog);
	~AudioLogger() = default;
	AudioLogger(const AudioLogger& other) = delete;
	AudioLogger(AudioLogger&& other) noexcept = delete;
	AudioLogger& operator=(const AudioLogger& other) = delete;
	AudioLogger& operator=(AudioLogger&& other) noexcept = delete;

	void Start() override;
	void End() override;
	void Update() override;
	void PlaySound(int soundId, int volume) override;
	void StopSound(int soundId) override;

	void AddAudioFile(const char* fileName) override;
private:
	AudioInterface* m_CurrentAudioSystem{ nullptr };
};
