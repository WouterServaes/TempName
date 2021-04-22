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
	m_AudioThread = std::thread([this] {Update(); });
}

void dae::GameAudio::End()
{
	m_AudioThread.join();
	endAudio();
}

void dae::GameAudio::PlaySound(int soundId, int volume)
{
	//
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_SoundQueue.size() >= MaxPendingSounds) throw(std::exception("GameAudio::PlaySound() => exceeded event queue events"));

		const PlayMessage pm{ soundId, volume };
		m_SoundQueue.push_back(pm);
	}
	//
}

void dae::GameAudio::StopSound(int)
{
	throw(std::exception("GameAudio::StopSound() => StopSound has not been implemented"));
}

//this Update runs on a separate thread
void dae::GameAudio::Update()
{
	std::unique_lock<std::mutex> uniqueLock(m_Mutex);
	m_ConditionVariable.wait(uniqueLock, [this] {return m_SoundQueue.size() > 0; });
	
	for (auto pm : m_SoundQueue)
		playSound(m_AudioFiles[m_AudioIds[pm.id]].c_str(), pm.volume);

	m_SoundQueue.clear();
}