#include "MiniginPCH.h"
#include "QBert_Comp.h"

#include "Events.h"
#include "GameObject.h"
#include "Health_Comp.h"
#include "Subject.h"

#include "AudioServiceLocator.h"

void QBert_Comp::Start()
{
	AudioServiceLocator::GetAudio()->AddAudioFile("../Data/Audio/hurt_sound.wav");
	m_pHealthComp = m_pGameObject->GetComponent<Health_Comp>();
}

void QBert_Comp::Update()
{
	if (m_pHealthComp->GetHealth() <= 0.f)
	{
		m_pHealthComp->RemoveLives(1);
		const auto volume = 50,
			soundId = 0;
		AudioServiceLocator::GetAudio()->PlaySound(soundId, volume);
		m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::LostLive);
		m_pHealthComp->ResetHealth();
	}

	if (m_pHealthComp->GetLives() <= 0)
		m_pGameObject->GetSubject()->Notify(m_pGameObject->GetGameObject(L"DeadText"), Event::PlayerDied);
}