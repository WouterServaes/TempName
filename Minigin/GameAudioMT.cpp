#include "MiniginPCH.h"
#include "GameAudioMT.h"

#include <thread>

#include "../3rdParty/Simple-SDL2-Audio/audio.h"

#pragma warning(push)
#pragma warning (disable:4244) //'=': conversion from 'int' to uint8_t', possible loss of data
#include "../3rdParty/Simple-SDL2-Audio/audio.c"
#pragma warning(pop)

void GameAudioMT::Start()
{
	// Initialize SDL audio
	_putenv("SDL_AUDIODRIVER=DirectSound");
	SDL_Init(SDL_INIT_AUDIO);
	// Initialize Simple-SDL2-Audio
	initAudio();
	m_AudioThread = std::thread([this] {HandleSoundQueue(); });
}

void GameAudioMT::End()
{
	m_EndAudio.store(true);
	m_ConditionVariable.notify_all();
	m_AudioThread.join();
	endAudio();
}

void GameAudioMT::PlaySound(const int soundId, const int volume)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	if (m_SoundQueue.size() >= MaxPendingSounds) Logger::LogError("GameAudioMT::PlaySound() => exceeded event queue events");

	const PlayMessage pm{ soundId, volume };
	m_SoundQueue.push_back(pm);
	m_ConditionVariable.notify_all();
}

void GameAudioMT::StopSound(int)
{
	Logger::LogError("GameAudioMT::StopSound() => StopSound has not been implemented");
}

void GameAudioMT::Update()
{
}

//this function runs on a separate thread
void GameAudioMT::HandleSoundQueue()
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

void GameAudioMT::AddAudioFile(const char* fileName)
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