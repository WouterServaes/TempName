#include "MiniginPCH.h"
#include "QBert_Comp.h"


#include "Events.h"
#include "GameObject.h"
#include "Health_Comp.h"
#include "Subject.h"

#include "ServiceLocator.h"

void dae::QBert_Comp::Start()
{
	ServiceLocator::GetAudio()->AddSoundFile("../Data/hurt_sound.wav");
}

void dae::QBert_Comp::Update()
{
	if(!m_IsInitialized)
	{
		m_IsInitialized = true;
		m_pHealthComp = m_pGameObject->GetComponent<Health_Comp>();
	}
	
	if(m_pHealthComp->GetHealth()<=0.f)
	{
		m_pHealthComp->RemoveLives(1);
		ServiceLocator::GetAudio()->PlaySound(0, 50);
		m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::LostLive);
		m_pHealthComp->ResetHealth();
	}

	if (m_pHealthComp->GetLives() <= 0)
		m_pGameObject->GetSubject()->Notify(m_pGameObject->GetGameObject(L"DeadText"), Event::PlayerDied);
}
