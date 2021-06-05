#include "MiniginPCH.h"
#include "GameAudio.h"
#include "../3rdParty/Simple-SDL2-Audio/audio.h"
//Already defined in GameAudioMT.cpp:
//#pragma warning(push)
//#pragma warning (disable:4244) //'=': conversion from 'int' to uint8_t', possible loss of data
//#include "../3rdParty/Simple-SDL2-Audio/audio.c"
//#pragma warning(pop)
//

void GameAudio::Start()
{
	// Initialize SDL audio
	_putenv("SDL_AUDIODRIVER=DirectSound");
	SDL_Init(SDL_INIT_AUDIO);
	// Initialize Simple-SDL2-Audio
	initAudio();
}

void GameAudio::End()
{
	endAudio();
}

void GameAudio::Update()
{
}

void GameAudio::PlaySound(const int soundId, const int volume)
{
	const auto file{ m_AudioFiles.at(m_AudioIds.at(soundId)) };
	playSound(file.c_str(), volume);
}

void GameAudio::StopSound(int )
{
	Logger::LogError("GameAudio::StopSound() => StopSound has not been implemented");
}

void GameAudio::AddAudioFile(const char* fileName)
{
	const auto it{ std::find(m_AudioFiles.begin(), m_AudioFiles.end(), fileName) };

	if (it == m_AudioFiles.end())
	{
		m_AudioIds.push_back(static_cast<int>(m_AudioIds.size()));
		m_AudioFiles.push_back(fileName);
	}
	else
		m_AudioIds.push_back(static_cast<int>(std::distance(m_AudioFiles.begin(), it)));
}