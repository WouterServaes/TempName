#pragma once
#include "NullAudio.h"
#include "AudioInterface.h"
//https://gameprogrammingpatterns.com/service-locator.html

class AudioServiceLocator final
{
public:
	AudioServiceLocator() = delete;
	~AudioServiceLocator() = default;
	AudioServiceLocator(const AudioServiceLocator& other) = delete;
	AudioServiceLocator(AudioServiceLocator&& other) noexcept = delete;
	AudioServiceLocator& operator=(const AudioServiceLocator& other) = delete;
	AudioServiceLocator& operator=(AudioServiceLocator&& other) noexcept = delete;

	static AudioInterface* GetAudio() { return m_pAudioService; }

	static void Initialize() { m_pAudioService = &m_NullAudioService; };

	/// <summary>
	/// Sets the current audio service to given audio interface.
	/// Sets current audio service to NullAudioService if given service is nullptr
	/// </summary>
	static void ProvideAudioService(AudioInterface* pBaseAudio)
	{
		if (pBaseAudio == nullptr)
			m_pAudioService = &m_NullAudioService;
		else
			m_pAudioService = pBaseAudio;
	}

	/// <summary>
	/// Ends the current audio service and deletes it
	/// </summary>
	static void RemoveService()
	{
		m_pAudioService->End();
		delete m_pAudioService;
	};
private:
	static AudioInterface* m_pAudioService;
	static NullAudio m_NullAudioService;
};
