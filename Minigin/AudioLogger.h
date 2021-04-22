#pragma once
#include "BaseAudio.h"

class AudioLogger final:public dae::BaseAudio
{
public:
	AudioLogger(BaseAudio* audioToLog);
	void Start() override;
	void End() override;
	void Update() override;
	void PlaySound(int soundId, int volume) override;
	void StopSound(int soundId) override;

	void AddAudioFile(const char* fileName) override;
private:
	BaseAudio* m_CurrentAudioSystem{ nullptr };
};

