#pragma once
#include "Observer.h"
//https://gameprogrammingpatterns.com/observer.html
namespace dae
{
	class Subject
	{
	public:
		Subject() = default;
		~Subject();
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) noexcept = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) noexcept = delete;
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
		void Notify(GameObject* gameObject, Event event);
	private:
		Observer* m_pHeadObserver{ nullptr };
	};
}
