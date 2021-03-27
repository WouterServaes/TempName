#pragma once
#include "NullAudio.h"
#include "BaseAudio.h"
//https://gameprogrammingpatterns.com/service-locator.html
namespace dae
{
	class BaseAudio;
	class ServiceLocator final
	{
	public:
		
		static BaseAudio* GetAudio() { return m_pAudioService; }
		static void Initialize(){m_pAudioService = &m_NullAudioService;};
		static void ProvideAudioService(BaseAudio* pBaseAudio)
		{

			if (pBaseAudio == nullptr)
				m_pAudioService = &m_NullAudioService;
			else
				m_pAudioService = pBaseAudio;
			
		}
		static void RemoveService()
		{
			m_pAudioService->End();
			delete m_pAudioService;
		};
	private:
		static BaseAudio* m_pAudioService;
		static NullAudio m_NullAudioService;
	};

}

