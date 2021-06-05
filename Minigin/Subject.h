#pragma once
#include "Observer.h"
//https://gameprogrammingpatterns.com/observer.html

class Subject
{
public:
	Subject() = default;
	~Subject();
	Subject(const Subject& other) = delete;
	Subject(Subject&& other) noexcept = delete;
	Subject& operator=(const Subject& other) = delete;
	Subject& operator=(Subject&& other) noexcept = delete;

	/// <summary>
	/// Adds pObserver to the Subject
	/// </summary>
	void AddObserver(Observer* pObserver);

	//Removes pObserver from the Subject
	void RemoveObserver(Observer* pObserver);

	/// <summary>
	/// Notifies every Observer of the Subject with the Event
	/// </summary>
	/// <param name="gameObject"> GameObject ptr that gets passed to OnNotify of Observer </param>
	/// <param name="event">Events specified in Events.h</param>
	void Notify(GameObject* gameObject, Event event) const;
private:
	Observer* m_pHeadObserver{ nullptr };
};
