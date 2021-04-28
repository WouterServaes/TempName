#include "MiniginPCH.h"
#include "AudioServiceLocator.h"

AudioInterface* AudioServiceLocator::m_pAudioService = nullptr;
NullAudio AudioServiceLocator::m_NullAudioService;
