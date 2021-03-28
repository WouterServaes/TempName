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
	m_QuitAudio = true;
	endAudio();
}

void dae::GameAudio::PlaySound(int soundId, int volume)
{
	const int numPending{ m_NumPending.load() };
	if (numPending >= MaxPendingSounds) throw(std::exception("GameAudio::PlaySound() => exceeded event queue events"));

	m_SoundQueue[numPending].id = soundId;
	m_SoundQueue[numPending].volume = volume;
	m_NumPending.store(m_NumPending.load() + 1);
}

void dae::GameAudio::StopSound(int)
{
	throw(std::exception("GameAudio::StopSound() => StopSound has not been implemented"));
}


//this Update runs separately from the main game loop
void dae::GameAudio::Update()
{
	while (m_QuitAudio == false)
	{
		const int numPending{ m_NumPending.load() };
		for (int idx{}; idx < numPending; idx++)
		{
			playSound(m_AudioFiles[m_AudioIds[m_SoundQueue[idx].id]].c_str(), m_SoundQueue[idx].volume);
		}
		
		//what if m_NumPending changes while doing m_NumPending.store() ._.
		m_NumPending.store(m_NumPending.load() - numPending);
		std::this_thread::sleep_for(std::chrono::microseconds(20));


		
		//std::cout << "Sound done, new numPending = "<<m_NumPending.load()<<"\n";
		//while (!m_NumPending.compare_exchange_strong(m_NumPending, m_NumPending+1));
	}
}