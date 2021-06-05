#pragma once
#include <AudioInterface.h>

//Audio using Simple SDL2 Audio
class GameAudio final:public AudioInterface
{
public:
	GameAudio() = default;
	~GameAudio() = default;
	GameAudio(const GameAudio & other) = delete;
	GameAudio(GameAudio && other) noexcept = delete;
	GameAudio& operator=(const GameAudio & other) = delete;
	GameAudio& operator=(GameAudio && other) noexcept = delete;
	
	void Start() override;
	void End() override;
	void Update() override;
	void PlaySound(int soundId, int volume) override;
	void StopSound(int soundId) override;
	void AddAudioFile(const char* fileName) override;

private:
	std::vector<std::string> m_AudioFiles{};
	std::vector<int> m_AudioIds{};
};

