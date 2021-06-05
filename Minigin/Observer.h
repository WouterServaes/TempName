#pragma once
//https://gameprogrammingpatterns.com/observer.html

enum class Event;
class GameObject;
class Observer
{
public:
	friend class Subject;
	Observer() = default;
	virtual ~Observer() = default;
	Observer(const Observer& other) = delete;
	Observer(Observer&& other) noexcept = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other) noexcept = delete;

	/// <summary>
	/// Called from the Subject, defines what should happen when an event is called
	/// </summary>
	virtual void OnNotify(GameObject* pGameObject, Event event) = 0;
private:
	Observer* m_pNextObserver{ nullptr };
};
