#include "MiniginPCH.h"
#include "AudioServiceLocator.h"


dae::AudioInterface* dae::AudioServiceLocator::m_pAudioService = nullptr;
dae::NullAudio dae::AudioServiceLocator::m_NullAudioService;