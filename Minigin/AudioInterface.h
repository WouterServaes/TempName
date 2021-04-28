#pragma once

class AudioInterface
{
public:

	virtual ~AudioInterface() = default;
	AudioInterface() = default;
	AudioInterface(const AudioInterface& other) = delete;
	AudioInterface(AudioInterface&& other) noexcept = delete;
	virtual AudioInterface& operator=(const AudioInterface& other) = delete;
	virtual AudioInterface& operator=(AudioInterface&& other) noexcept = delete;

	virtual void Start() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void PlaySound(int soundId, int volume) = 0;
	virtual void StopSound(int soundId) = 0;
	virtual void AddAudioFile(const char* fileName) = 0;
};
