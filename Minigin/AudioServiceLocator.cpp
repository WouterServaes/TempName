#include "MiniginPCH.h"
#include "AudioServiceLocator.h"


dae::BaseAudio* dae::AudioServiceLocator::m_pAudioService = nullptr;
dae::NullAudio dae::AudioServiceLocator::m_NullAudioService;