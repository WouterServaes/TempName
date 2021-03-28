#include "MiniginPCH.h"
#include "GameAudio.h"

#include <thread>

#include "../3rdParty/Simple-SDL2-Audio/audio.h"

#pragma warning(push)
#pragma warning (disable:4244) //'=': conversion from 'int' to uint8_t', possible loss of data
#include "../3rdParty/Simple-SDL2-Audio/audio.c"
#pragma warning(pop)

void dae::GameAudio::Start()
{
	// Initialize SDL audio
	_putenv("SDL_AUDIODRIVER=DirectSound");
	SDL_Init(SDL_INIT_AUDIO);
	// Initialize Simple-SDL2-Audio
	initAudio();
}

void dae::GameAudio::End()
{
	endAudio();
}

void dae::GameAudio::PlaySound(int soundId, int volume)
{
	if (m_NumPending >= MaxPendingSounds) throw(std::exception("GameAudio::PlaySound() => exceeded event queue events"));

	m_SoundQueue[m_NumPending].id = soundId;
	m_SoundQueue[m_NumPending].volume = volume;
	m_NumPending++;
}

void dae::GameAudio::StopSound(int )
{
	throw(std::exception("GameAudio::StopSound() => StopSound has not been implemented"));
}

void dae::GameAudio::Update()
{

	auto processSoundQueue{[this]()
		{
			for (int idx{}; idx < m_NumPending; idx++)
			{
				playSound(m_AudioFiles[m_AudioIds[m_SoundQueue[idx].id]].c_str(), m_SoundQueue->volume);	
			}
			m_NumPending = 0;
			
		} };

	std::thread audioThread{ processSoundQueue };
	audioThread.detach();
}


