#include "MiniginPCH.h"
#include "GameAudio.h"

#include <thread>

#include "../3rdParty/Simple-SDL2-Audio/audio.h"

#pragma warning(push)
#pragma warning (disable:4244) //'=': conversion from 'int' to uint8_t', possible loss of data
#include "Logger.h"
#include "../3rdParty/Simple-SDL2-Audio/audio.c"
#pragma warning(pop)

void dae::GameAudio::Start()
{
	// Initialize SDL audio
	_putenv("SDL_AUDIODRIVER=DirectSound");
	SDL_Init(SDL_INIT_AUDIO);
	// Initialize Simple-SDL2-Audio
	initAudio();
	m_AudioThread = std::thread([this] {HandleSoundQueue(); });
}

void dae::GameAudio::End()
{
	m_EndAudio.store(true);
	m_ConditionVariable.notify_all();
	m_AudioThread.join();
	endAudio();
}

void dae::GameAudio::PlaySound(const int soundId, const  int volume)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	if (m_SoundQueue.size() >= MaxPendingSounds) Logger::LogError("GameAudio::PlaySound() => exceeded event queue events");

	const PlayMessage pm{ soundId, volume };
	m_SoundQueue.push_back(pm);
	m_ConditionVariable.notify_all();
}

void dae::GameAudio::StopSound(int)
{
	Logger::LogError("GameAudio::StopSound() => StopSound has not been implemented");
}

void dae::GameAudio::Update()
{
}

//this function runs on a separate thread
void dae::GameAudio::HandleSoundQueue()
{
	while (!m_EndAudio.load())
	{
		std::unique_lock<std::mutex> uniqueLock(m_Mutex);
		m_ConditionVariable.wait(uniqueLock, [this]
			{
				return m_SoundQueue.size() > 0 || m_EndAudio.load();
			});

		for (const auto& pm : m_SoundQueue)
			playSound(m_AudioFiles[m_AudioIds[pm.id]].c_str(), pm.volume);

		m_SoundQueue.clear();
	}
}

void dae::GameAudio::AddAudioFile(const char* fileName)
{
	const auto it{ std::find_if(m_AudioFiles.begin(), m_AudioFiles.end(), [fileName](const std::string& str)
		{
			return str == fileName;
		}) };

	if (it == m_AudioFiles.end())
	{
		m_AudioIds.push_back(static_cast<int>(m_AudioIds.size()));
		m_AudioFiles.push_back(fileName);
	}
	else
		m_AudioIds.push_back(static_cast<int>(std::distance(m_AudioFiles.begin(), it)));
}