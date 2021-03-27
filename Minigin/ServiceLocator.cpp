#include "MiniginPCH.h"
#include "ServiceLocator.h"


dae::BaseAudio* dae::ServiceLocator::m_pAudioService = nullptr;
dae::NullAudio dae::ServiceLocator::m_NullAudioService;