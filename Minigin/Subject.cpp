#include "MiniginPCH.h"
#include "Subject.h"

void dae::Subject::AddObserver(Observer* pObserver) //adds observer at the end of the observer chain
{
	if (m_pHeadObserver == nullptr)
	{
		m_pHeadObserver = pObserver;
		return;
	}

	auto* current{ m_pHeadObserver };

	while (current != nullptr)
	{
		if (current->m_pNextObserver == nullptr)
		{
			current->m_pNextObserver = pObserver;
			return;
		}
		current = current->m_pNextObserver;
	}
}

void dae::Subject::RemoveObserver(Observer* pObserver)
{
	if(m_pHeadObserver == pObserver)
	{
		m_pHeadObserver = pObserver->m_pNextObserver;
		pObserver->m_pNextObserver = nullptr;
		return;
	}

	auto* current{m_pHeadObserver};
	while(current!= nullptr)
	{
		if(current->m_pNextObserver == pObserver)
		{
			current->m_pNextObserver = pObserver->m_pNextObserver;
			pObserver->m_pNextObserver = nullptr;
			return;
		}
		current = current->m_pNextObserver;
	}
}

void dae::Subject::Notify(const GameObject* gameObject, Event event)
{
	auto* current = m_pHeadObserver;
	while(current!= nullptr)
	{
		current->OnNotify(gameObject, event);
		current = current->m_pNextObserver;
		
	}
}