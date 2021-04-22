#pragma once
#include "AudioInterface.h"

class AudioLogger final:public dae::AudioInterface
{
public:
	AudioLogger(AudioInterface* audioToLog);
	void Start() override;
	void End() override;
	void Update() override;
	void PlaySound(int soundId, int volume) override;
	void StopSound(int soundId) override;

	void AddAudioFile(const char* fileName) override;
private:
	AudioInterface* m_CurrentAudioSystem{ nullptr };
};

